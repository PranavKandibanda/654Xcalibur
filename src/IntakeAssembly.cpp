#include "vex.h"
#include "IntakeAssembly.h"
#include "robot-config.h" // for hook
#include "PistonAssembly.h"
#include "mikLib/globals.h" // for alliance_is_red

using namespace vex;

IntakeAssembly::IntakeAssembly(
    mik::motor_group intake,
    mik::motor main_intake_motor,
    mik::motor outake_motor,
    mik::motor front_intake_motor,
    mik::distance ball_sensor
) :
    intake(intake),
    main_intake_motor(main_intake_motor),
    outake_motor(outake_motor),
    front_intake_motor(front_intake_motor),
    ball_sensor(ball_sensor)
{
}

void IntakeAssembly::init() {
    control();
    scraper.set(false); // Retract scraper
    hook.set(false);    // Retract hook
    park.set(false);    // Retract park
    changePiston.set(false); // Retract change piston
}

void IntakeAssembly::control() {
    intake_motors_control();
}

// Requires: #include "mikLib/UI/UI_manager.h" for auton_scr
void IntakeAssembly::intake_motors_control() {

    if (Controller.ButtonL1.pressing()) {
        // Always pull game pieces in with the main and front intakes
        main_intake_motor.spin(forward, 15, volt);
        front_intake_motor.spin(forward, 15, volt);
        /*if (ball_sensor.objectDistance(inches) < 1.5) {
            outake_motor.stop(brake);
        } else {
            outake_motor.spin(forward,15,volt);
        }*/
        outake_motor.spin(forward,15,volt);

    }
    else if (Controller.ButtonL2.pressing()) {
        changePiston.set(true);
        main_intake_motor.spin(reverse, 15, volt);
        front_intake_motor.spin(reverse, 15, volt);
        outake_motor.spin(reverse,15,volt);
    }
    else {
        main_intake_motor.stop(brake);
        front_intake_motor.stop(brake);
        outake_motor.stop(brake);
    }
}

