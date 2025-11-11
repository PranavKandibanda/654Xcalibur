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
    mik::motor front_intake_motor
) :
    intake(intake),
    main_intake_motor(main_intake_motor),
    outake_motor(outake_motor),
    front_intake_motor(front_intake_motor)
{
}

void IntakeAssembly::init() {
    control();
}

void IntakeAssembly::control() {
    intake_motors_control();
}

// Requires: #include "mikLib/UI/UI_manager.h" for auton_scr
void IntakeAssembly::intake_motors_control() {

    if (Controller.ButtonL1.pressing()) {
        // Always pull game pieces in with the main and front intakes
        main_intake_motor.spin(forward, 12, volt);
        front_intake_motor.spin(forward, 12, volt);
        outake_motor.spin(forward,12,volt);
    }
    else if (Controller.ButtonL2.pressing()) {
        main_intake_motor.spin(reverse, 12, volt);
        front_intake_motor.spin(reverse, 12, volt);
        outake_motor.spin(reverse,12,volt);
    }
    else if(Controller.ButtonUp.pressing()) {
        // Slow outtake for balancing
        changePiston.set(true);
    }
    else if(Controller.ButtonDown.pressing()) {
        // Slow outtake for balancing
        changePiston.set(false);
    }
    else {
        main_intake_motor.stop(brake);
        front_intake_motor.stop(brake);
        outake_motor.stop(brake);
    }
}

