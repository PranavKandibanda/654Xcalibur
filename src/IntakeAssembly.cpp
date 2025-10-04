#include "vex.h"
#include "IntakeAssembly.h"
#include "robot-config.h" // for hook
#include "PistonAssembly.h"
#include "mikLib/globals.h" // for alliance_is_red

using namespace vex;

IntakeAssembly::IntakeAssembly(
    mik::motor_group intake,
    mik::motor main_intake_motor, 
    mik::motor color_sense_motor,
    mik::motor front_intake_motor,
    vex::optical color_sensor
) :
    intake(intake),
    main_intake_motor(main_intake_motor),
    color_sense_motor(color_sense_motor),
    front_intake_motor(front_intake_motor),
    color_sensor(color_sensor)
{}

void IntakeAssembly::init() {
}

void IntakeAssembly::control() {
    intake_motors_control();
}

// Requires: #include "mikLib/UI/UI_manager.h" for auton_scr
void IntakeAssembly::intake_motors_control() {
    // Get alliance color from global (true=red, false=blue)
    bool is_red_alliance = mik::alliance_is_red;

    if (Controller.ButtonL1.pressing()) {
        // Always pull game pieces in with the main and front intakes
        main_intake_motor.spin(forward, 12, volt);
        front_intake_motor.spin(forward, 12, volt);
        color_sensor.setLightPower(100);
        color_sensor.setLight(vex::ledState::on);
        if (hook.extended) {
            // Hold roller still if hook is engaged
            if(color_sensor.isNearObject())
            {
                color_sense_motor.spin(forward, 6, volt);
                vex::task::sleep(100);
                color_sense_motor.stop(brake);
            }
        } else {
            // Simple hue check to decide if this piece matches our alliance
            double hue = color_sensor.hue(); // 0-360
            bool same_color = is_red_alliance
                ? (hue >= 20 && hue <= 40)      // red band
                : (hue >= 160 && hue <= 200);   // blue band

            if (same_color) {
                color_sense_motor.spin(forward, 12, volt);
            } else {
                color_sense_motor.spin(reverse, 12, volt);
            }
        }
    } 
    else if (Controller.ButtonL2.pressing()) {
        main_intake_motor.spin(reverse, 12, volt);
        front_intake_motor.spin(reverse, 12, volt);
        color_sense_motor.spin(reverse,12,volt);
    }
    else {
        intake.stop(brake);
        main_intake_motor.stop(brake);
        color_sense_motor.stop(brake);
        front_intake_motor.stop(brake);
    }
}
