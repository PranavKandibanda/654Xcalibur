#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/imu.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "robodash/api.h"
#include "autons.h"
//sudo chmod 666 /dev/ttyACM0
// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
pros::MotorGroup leftMotors({-15, 14, -13},
                            pros::MotorGearset::blue); // left motor group - ports 3 (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors({17, -16, 18}, pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

pros::Motor intake_stage1 (4, pros::MotorGearset::blue); // intake stage 1 motor on port 1
pros::Motor intake_stage2 (-10, pros::MotorGearset::blue); // intake stage 2 motor on port 2

// Inertial Sensor on port 10
pros::Imu imu(8);

//pneumatics
pros::adi::Pneumatics hook_piston('C',false); //hook piston on port A
pros::adi::Pneumatics scraper_piston('B',false); //hook piston on port A
pros::adi::Pneumatics middle('A',false); //middle piston on port C
//pneumatics



// tracking wheels
// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
pros::Rotation horizontalEnc(12);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
pros::Rotation verticalEnc(-19);
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_2, -3.25);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_2, -1);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11, // 11 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              480, // drivetrain rpm is 360
                              2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(7.35, // proportional gain (kP)
                                            .2, // integral gain (kI)
                                            20, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                    500, // large error range timeout, in milliseconds
                                            7 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(1.5, // proportional gain (kP)
                                             .2, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0   // maximum acceleration (slew)
);

// sensors for odometry
lemlib::OdomSensors sensors(&vertical, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal, // horizontal tracking wheel
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

void intake()
{
    intake_stage1.move(127);
    intake_stage2.move(127);
}

void outtake()
{
    intake_stage1.move(-127);
    intake_stage2.move(-127);
}

void load()
{
    middle.set_value(true);
    intake_stage1.move(127);
    intake_stage2.move(-127);
}

void stop_load()
{
    intake_stage1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    intake_stage2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    intake_stage1.brake();
    intake_stage2.brake();
}



rd::Selector selector({
    {"Blue 3 + 3 Left", blue_3_3_auton_left},
    {"Skills", skills},
    {"PID Test Linear", pid_test_linear},
    {"PID Test Angular", pid_test_angular}
});

void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    //selector.focus();
    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
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

// get a path used for pure pursuit
// this needs to be put outside a function

/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */

void autonomous() {
	//selector.run_auton();
    blue_3_3_auton_left();
    //skills();
}

/**
 * Runs in driver control
 */
void opcontrol() {
    autonomous();
    // controller
    // loop to continuously update motors
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
            hook_piston.toggle();
            pros::delay(200);
        }
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
            intake();
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
            middle.set_value(false);
            intake();
        }
        else {
            intake_stage1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            intake_stage2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            intake_stage1.brake();
            intake_stage2.brake();
        }
        if (controller.get_digital_new_release(pros:: E_CONTROLLER_DIGITAL_R2))
        {
            middle.set_value(true);
            pros::delay(200);
        }

    }
}