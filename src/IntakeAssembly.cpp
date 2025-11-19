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
}

void IntakeAssembly::control() {
    intake_motors_control();
}

// Requires: #include "mikLib/UI/UI_manager.h" for auton_scr
void IntakeAssembly::intake_motors_control() {

    // detect X to toggle the behavior
    /*bool cur_X = Controller.ButtonX.pressing();
    if (cur_X && !prev_button_l1) {
        // If prev was not pressed and currently pressed, flip the keep-moving flag
        l1_keep_moving = !l1_keep_moving;
    }
    // Update previous state (store true if pressed now)
    prev_button_l1 = cur_X;*/

    if (Controller.ButtonL1.pressing()) {
        // Always pull game pieces in with the main and front intakes
        main_intake_motor.spin(forward, 12, volt);
        front_intake_motor.spin(forward, 12, volt);
        /*if (ball_sensor.objectDistance(inches) < 1.5) {
            if (l1_keep_moving) {
                // keep moving even when a ball is detected
                outake_motor.spin(forward, 12, volt);
            } else {
                // brake when a ball is detected
                outake_motor.stop(brake);
            }
        } else {
            outake_motor.spin(forward,12,volt);
        }*/
       outake_motor.spin(forward,12,volt);

    }
    else if (Controller.ButtonL2.pressing()) {
        changePiston.set(true);
        main_intake_motor.spin(reverse, 12, volt);
        front_intake_motor.spin(reverse, 12, volt);
        outake_motor.spin(reverse,12,volt);
    }
    else {
        main_intake_motor.stop(brake);
        front_intake_motor.stop(brake);
        outake_motor.stop(brake);
    }
}

