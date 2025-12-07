#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "robodash/api.h"

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
pros::MotorGroup leftMotors({-14, -6, 10},
                            pros::MotorGearset::blue); // left motor group - ports 3 (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors({7, 4, -19}, pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

// intake motors
pros::Motor ElevenStg1(-17, pros::MotorGearset::blue);
pros::Motor FiveStg1(-13, pros::MotorGearset::blue);
pros::Motor FiveStg2(16, pros::MotorGearset::blue);

//pnuematic pistons
pros::adi::Pneumatics hook_piston('H',false);
pros::adi::Pneumatics scraper_piston('F',false);
pros::adi::Pneumatics change_piston('G',false);

// Inertial Sensor on port 10
pros::Imu imu(19);

// tracking wheels
// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
pros::Rotation horizontalEnc(12);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
pros::Rotation verticalEnc(-20);
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, .5);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, 1);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 4" omnis
                              360, // drivetrain rpm is 360
                              8 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(1.35, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            9, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(.304, // proportional gain (kP)
                                             .005, // integral gain (kI)
                                             4.026, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
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
void load_balls () {
	ElevenStg1.move_velocity(127);
	FiveStg1.move_velocity(127);
	FiveStg2.move_velocity(-127);
}

void score_balls () {
	ElevenStg1.move_velocity(127);
	FiveStg1.move_velocity(127);
	FiveStg2.move_velocity(-127);
}

void score_low () {
	ElevenStg1.move_velocity(-127);
	FiveStg1.move_velocity(-127);
	FiveStg2.move_velocity(-127);
}

void stop_intake () {
	ElevenStg1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	FiveStg1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	FiveStg2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	ElevenStg1.brake();
	FiveStg1.brake();
	FiveStg2.brake();
}

void unjam () {
	ElevenStg1.move_velocity(-127);
	FiveStg1.move_velocity(-127);
	FiveStg2.move_velocity(-127);
	pros::delay(500);

	ElevenStg1.move_velocity(127);
	FiveStg1.move_velocity(127);
	FiveStg2.move_velocity(127);
	pros::delay(500);
}
// autonomous routines
void blue_left() {
    //gets 3 center, 2 under goal, 3 from loader
    chassis.setPose(48.567,-16.405,270);

	chassis.moveToPose(31.024,-16.405,240,500,{},false);

	chassis.moveToPose(3.913,-46.441, 215, 1000,{},false);
	//capturing center 3 balls
	load_balls();
	chassis.waitUntil(3);
	scraper_piston.set_value(true);
	chassis.waitUntil(12);
	scraper_piston.set_value(false);
	//capturing center 3 balls

	//capturing 2 under goal
	chassis.waitUntil(30);
	scraper_piston.set_value(true);
	chassis.waitUntilDone();
	stop_intake();
	//capturing 2 under goal

	//scoring all 5 balls
	chassis.moveToPose(26.24, -36.34, 132, 500);
	unjam();
	chassis.waitUntilDone();
	chassis.moveToPose(27.303, -47.238, 270, 500,{},false);
	score_balls();
	pros::delay(2000);
	stop_intake();
	//scoring all 5 balls

	//getting 3 from loader
	chassis.moveToPose(56.807,-46.972,0,400,{},false);
	scraper_piston.set_value(true);
	load_balls();
	chassis.moveToPose(58.136, -46.972, 0,100, {}, false);
	pros::delay(1000);
	stop_intake();
	//getting 3 from loader

	//scoring 3 from loader
	chassis.moveToPoint(46.441, -47.238, 200,{},false);
	scraper_piston.set_value(false);
	chassis.moveToPose(27.303,-47.238,270,500,{},false);
	score_balls();
	pros::delay(2000);
	//scoring 3 from loader
}

/*void blue_right() {

};

void red_left() {

};

void red_right() {

};*/

rd::Selector selector({
    {"Blue Left", blue_left}//,
    /*{"Blue Right", blue_right},
    {"Red Left", red_left},
	{"Red Right", red_right},*/
});

void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
	selector.focus();
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
ASSET(example_txt); // '.' replaced with "_" to make c++ happy


/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */
void autonomous() {
    selector.run_auton();
}

/**
 * Runs in driver control
 */
void opcontrol() {
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


    }
}