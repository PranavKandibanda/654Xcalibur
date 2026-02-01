#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "api.h" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/motor_group.hpp"
#include "pros/rtos.hpp"
#include <cstdlib>

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
pros::MotorGroup leftMotors({-6, -5, -4},pros::MotorGearset::blue); // left motor group - ports 3 (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors({8, 9, 10}, pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)
pros::MotorGroup intake({3,-7}, pros::MotorGearset::blue);
// Inertial Sensor on port 10
pros::Imu imu(21);
pros::Distance east(16);
pros::Distance north(2);
pros::Distance west(1);
pros::Distance south(11);

// Pneumatics
pros::adi::Pneumatics hook_piston('G',false);
pros::adi::Pneumatics scraper_piston('H',false);

pros::adi::Pneumatics loading_piston('B',false);
pros::adi::Pneumatics scoring_piston('C',false);

constexpr double FIELD_SIZE_MM  = 3657.6/25.4;
// Positive values = outward from center
// Measured from tracking center to sensor (mm)
// +X = east, +Y = north
constexpr double NORTH_Y_OFFSET_MM = 228.6/25.4;
constexpr double SOUTH_Y_OFFSET_MM = 101.6/25.4;
constexpr double EAST_X_OFFSET_MM  = 152.4/25.4;
constexpr double WEST_X_OFFSET_MM  = 152.4/25.4;


// Distance from robot center to the distance sensor face
constexpr double ROBOT_RADIUS_MM = 180.0; // adjust to your robot

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              10.625, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              8 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(14, // proportional gain (kP)
                                            .01, // integral gain (kI)
                                            240, // derivative gain (kD)
                                            3, // anti windup
                                            4, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            6, // large error range, in inches
                                            300, // large error range timeout, in milliseconds
                                            6 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(4.1, // proportional gain (kP)
                                             .18, // integral gain (kI)
                                             30, // derivative gain (kD)
                                             10, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            nullptr, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        while (true) {

            //printf("X: %f", chassis.getPose().x); // x
            //printf("Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "X: %f", chassis.getPose().x); // heading
            pros::lcd::print(3, "Y: %f", chassis.getPose().y); // heading
            pros::lcd::print(4, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });

}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}


/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */

double normalizeAngle(double deg) {
  while (deg < 0) deg += 360;
  while (deg >= 360) deg -= 360;
  return deg;
}

void distanceResetPose() {
  double thetaDeg = chassis.getPose().theta;
  thetaDeg = normalizeAngle(thetaDeg);

  auto pose = chassis.getPose();
  double x = pose.x;
  double y = pose.y;

  // Facing EAST (wall at +X)
  if (thetaDeg >= 315 || thetaDeg < 45) {
    double d = east.get_distance()/25.4;
    x = FIELD_SIZE_MM - d - EAST_X_OFFSET_MM;
  }
  // Facing NORTH (wall at +Y)
  else if (thetaDeg >= 45 && thetaDeg < 135) {
    double d = east.get_distance()/25.4;
    y = -(FIELD_SIZE_MM/2 - d - EAST_X_OFFSET_MM);
  }
  // Facing WEST (wall at 0)
  else if (thetaDeg >= 135 && thetaDeg < 225) {
    double d = west.get_distance()/25.4;
    double d2 = north.get_distance()/25.4;
    x = FIELD_SIZE_MM/2 - d - WEST_X_OFFSET_MM;
    y = -(FIELD_SIZE_MM/2 - d2 - NORTH_Y_OFFSET_MM);
    //pros::lcd::print(5, "West distance: %f", y);
  }
  // Facing SOUTH (wall at 0)
  else {
    double d = south.get_distance()/25.4;
    y = 0.0 - d - SOUTH_Y_OFFSET_MM;
  }
  chassis.setPose(x, y, thetaDeg);
}

void autonomous() {
    chassis.setPose(0,0,0);
    /*pros::Task desmosTask([&]() {
        // configure desmos logger
        while(true){
            // log position to desmos
            printf("(%f, %f)\n", chassis.getPose().x, chassis.getPose().y);
            // delay to save resources
            pros::delay(50);
        }
    });*/
    /*chassis.moveToPoint(0,6,1000,{},false);
    chassis.moveToPoint(0,18,1000,{},false);
    chassis.moveToPoint(0, 24, 1000,{},false); // move to (0,24) with a timeout of 1000ms
    chassis.moveToPoint(0,0,1000,{.forwards = false},false);*/

    chassis.setPose(0,0,0);
    chassis.turnToHeading(45,999,{},false);
    chassis.turnToHeading(90,999,{},false);
    //chassis.turnToHeading(135,999,{},false);
    chassis.turnToHeading(180,999,{},false);
    chassis.turnToHeading(270,999,{},false);
    chassis.turnToHeading(0,999,{},false);
    chassis.turnToHeading(180,999,{},false);
    
}

void score()
{
    scoring_piston.set_value(false);
    loading_piston.set_value(false);
    intake.move(127);
}

void outtake()
{
    scoring_piston.set_value(false);
    loading_piston.set_value(false);
    intake.move(-127);
}

void load()
{
    scoring_piston.set_value(true);
    loading_piston.set_value(true);
    intake.move(127);
}

void middle()
{
    scoring_piston.set_value(false);
    loading_piston.set_value(true);
    intake.move(127);
}

void score_setup()
{
  scoring_piston.set_value(false);
  loading_piston.set_value(false);
}

void four_3_left()
{
    scraper_piston.set_value(false);
    chassis.setPose(0,0,180);
    distanceResetPose();
    chassis.setPose(chassis.getPose().x,-14,180);

    chassis.moveToPoint(46.5, -46,1000, {},false);
    scraper_piston.set_value(true);
    load();

    chassis.turnToHeading(90, 1000,{},false);
    distanceResetPose();
    chassis.arcade(80, 0);
    pros::Task::delay(1000);

    chassis.moveToPoint(29.7+2, -47.5, 1000, {.forwards = false},false);
    score();
    pros::delay(1000);

    scraper_piston.set_value(false);
    chassis.setPose(15,-48,90);

    chassis.moveToPoint(22, -48, 1000, {}, false);
    load();

    chassis.moveToPose(21, -24-2, -50, 1000,{},false);
    pros::delay(500);

    chassis.arcade(60, 0);
    pros::delay(1000);
    chassis.turnToPoint(0,0,1000,{.forwards = false},false);
    chassis.moveToPose(10, -10, 135+180-15, 1000,{.forwards=false}, false);
    score();
}

/**
 * Runs in driver control
 */
void opcontrol() {
    // controller
    // loop to continuously update motors
    //autonomous();
    four_3_left();
    while (true) {
        // get joystick positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        // move the chassis with curvature drive
        chassis.arcade(leftY, rightX);
        // delay to save resources
        pros::delay(10);

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
        {
            scraper_piston.toggle();
            pros::delay(200);
        }
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B))
        {
            hook_piston.set_value(false);
        }
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
            score();
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
            outtake();
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
        {
            load();
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
        {
            middle();
        }
        else {
            intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
            intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
            intake.brake();
            intake.brake();
        }
        if (controller.get_digital_new_release(pros:: E_CONTROLLER_DIGITAL_R2))
        {
            scoring_piston.set_value(true);
            loading_piston.set_value(true);
        }
        else if(controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_B))
        {
            hook_piston.set_value(true);
            pros::delay(200);
        }
    }
}