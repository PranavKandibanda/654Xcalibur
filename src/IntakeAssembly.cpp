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
    control();
}

void IntakeAssembly::control() {
    //intake_motors_control();
    skills_control();
}

// Requires: #include "mikLib/UI/UI_manager.h" for auton_scr
void IntakeAssembly::intake_motors_control() {

    if (Controller.ButtonL1.pressing()) {
        // Always pull game pieces in with the main and front intakes
        main_intake_motor.spin(forward, 12, volt);
        front_intake_motor.spin(forward, 12, volt);
        color_sensor.setLight(vex::ledState::on);
        color_sensor.setLightPower(100);
        // Simple hue check to decide if this piece matches our alliance
        color_sort();
    }
    else if (Controller.ButtonL2.pressing()) {
        main_intake_motor.spin(reverse, 12, volt);
        front_intake_motor.spin(reverse, 12, volt);
        color_sense_motor.spin(reverse,12,volt);
    }
    else if(Controller.ButtonDown.pressing()) {
        // Slow outtake for balancing
        main_intake_motor.spin(reverse, 12, volt);
        front_intake_motor.spin(reverse, 12, volt);
        color_sort(true);
    }
    else {
        main_intake_motor.stop(brake);
        front_intake_motor.stop(brake);
        color_sense_motor.stop(brake);
        color_sensor.setLight(vex::ledState::off);
    }
}

void IntakeAssembly::skills_control() {
    if (Controller.ButtonL1.pressing()) {
        // Always pull game pieces in with the main and front intakes
        intakeAssembly.main_intake_motor.spin(forward, 12, volt);
        intakeAssembly.front_intake_motor.spin(forward, 12, volt);
        intakeAssembly.color_sense_motor.spin(forward,12,volt);
        // Simple hue check to decide if this piece matches our alliance
    }
    else if (Controller.ButtonL2.pressing()) {
        intakeAssembly.main_intake_motor.spin(reverse, 12, volt);
        intakeAssembly.front_intake_motor.spin(reverse, 12, volt);
        intakeAssembly.color_sense_motor.spin(reverse,12,volt);
    }
    else if(Controller.ButtonDown.pressing()) {
        // Slow outtake for balancing
        intakeAssembly.main_intake_motor.spin(reverse, 12, volt);
        intakeAssembly.front_intake_motor.spin(reverse, 12, volt);
        intakeAssembly.color_sense_motor.spin(reverse, 12, volt);
    }
    else {
        intakeAssembly.main_intake_motor.stop(brake);
        intakeAssembly.front_intake_motor.stop(brake);
        intakeAssembly.color_sense_motor.stop(brake);
    }
}
void IntakeAssembly::color_sort(bool reverse_sort)
{
// Always pull game pieces in with the main and front intakes
    main_intake_motor.spin(forward, 12, volt);
    front_intake_motor.spin(forward, 12, volt);
    color_sensor.setLightPower(100);
    color_sensor.setLight(vex::ledState::on);
    // Simple hue check to decide if this piece matches our alliance
    if (reverse_sort)
    {
        if (color_sensor.isNearObject())
        {
            if(hook.extended)
            {
                color_sort_tech(true,true);
                
            }
            else
            {
                color_sort_tech(true,false);
            }
        }
    }
    else
    {
        if (color_sensor.isNearObject())
        {
            if(hook.extended)
            {
                color_sort_tech(false,true);
                
            }
            else
            {
                color_sort_tech(false,false);
            }
        }
        else
        {
            color_sense_motor.spin(forward, 12,volt);
        }
    }
}

void IntakeAssembly::color_sort_tech(bool reverse_sort,bool hook_mech)
{
    bool is_red_alliance = mik::alliance_is_red;
    double hue = color_sensor.hue(); // 0-360
    bool same_color = is_red_alliance
    ? (hue >= 0 && hue <= 60)      // red band
    : (hue >= 160 && hue <= 250);   // blue band
    if (reverse_sort) {
        if (!same_color) {
            color_sense_motor.spin(forward, 12, volt);
        } 
        else{
            color_sense_motor.spin(reverse, 12,volt);
        }
    }
    else{
        if (hook_mech) {
            if (color_sensor.isNearObject())
            {
                if (same_color) {
                    color_sense_motor.spin(forward, 12, volt);
                    wait(.05,sec);
                    color_sense_motor.stop(brake);
                }
                else if (!same_color)
                {
                    color_sense_motor.spin(reverse,12,volt);
                } 
                else
                {
                    color_sense_motor.spin(forward,12,volt);
                }
            }
            else {
                color_sense_motor.spin(forward, 12,volt);
            }
        }
        else
        {
            if (!same_color) {
                color_sense_motor.spin(reverse, 12, volt);
            } 
            else{
                color_sense_motor.spin(forward, 12,volt);
            }
        }
    }
}