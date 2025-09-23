#include "vex.h"
#include "IntakeAssembly.h"

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
    // Get alliance color from auton_scr->red_blue (true=red, false=blue)
    bool is_red_alliance = false;
    #ifdef AUTON_SCR_AVAILABLE
    is_red_alliance = auton_scr->red_blue;
    #endif

    static uint32_t last_color_check_time = 0;
    const uint32_t color_check_delay = 500; // ms
    uint32_t now = vex::timer::system();

    if (Controller.ButtonL1.pressing()) {
        main_intake_motor.spin(reverse, 12, volt);
        color_sense_motor.spin(reverse, 12, volt);
        front_intake_motor.spin(reverse, 12, volt);
        // No delay logic for manual reverse
    } 
    else if (Controller.ButtonL2.pressing()) {
        main_intake_motor.spin(forward, 12, volt);
        front_intake_motor.spin(forward, 12, volt);

        // Only check color and control color_sense_motor every color_check_delay ms
        if (now - last_color_check_time >= color_check_delay) {
            last_color_check_time = now;
            vex::color detected = color_sensor.color();
            bool is_item_red = (detected == vex::color::red);
            bool is_item_blue = (detected == vex::color::blue);

            if ((is_red_alliance && !is_item_red) || (!is_red_alliance && !is_item_blue)) {
                // Item is NOT alliance color: spin backwards
                color_sense_motor.spin(reverse, 12, volt);
            } else {
                // Item matches alliance color: spin forward
                color_sense_motor.spin(forward, 12, volt);
            }
        } // else: do not change color_sense_motor state
    }
    else {
        intake.stop(brake);
        main_intake_motor.stop(brake);
        color_sense_motor.stop(brake);
        front_intake_motor.stop(brake);
    }
}
