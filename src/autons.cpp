#include "vex.h"

using namespace vex;
using namespace mik;
#include "mikLib/globals.h"
#include "robot-config.h"
#include "PistonAssembly.h"

void default_constants(void) {
    chassis.set_control_constants(5, 10, 1.019, 5, 10, 1.019);

    // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
    chassis.set_turn_constants(12, .258, .004, 2.196, 45);
    chassis.set_drive_constants(12, 1.2, 0.04, 7.7, 3);
    chassis.set_heading_constants(6, .3, .1, 3, 0);
    chassis.set_swing_constants(12, .337, .0095, 3.486, 45);

    // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_turn_exit_conditions(1.5, 75, 2000);
    chassis.set_drive_exit_conditions(1, 75, 3000);
    chassis.set_swing_exit_conditions(1.25, 75, 3000);
}

void load()
{
    hook.toggle();
    intakeAssembly.main_intake_motor.spin(forward, 12, volt);
    intakeAssembly.color_sense_motor.spin(forward, 12, volt);
    intakeAssembly.front_intake_motor.spin(forward, 12, volt);
}

void unload(int height)
{
    hook.toggle();
    if (height >1)
    {
        intakeAssembly.main_intake_motor.spin(forward, 12, volt);
        intakeAssembly.color_sense_motor.spin(forward, 12, volt);
        if (height == 3)
        {
            intakeAssembly.front_intake_motor.spin(forward, 12, volt);
        }
        if (height == 2)
        {
            intakeAssembly.front_intake_motor.spin(reverse, 12, volt);
            
        }
    }
    else
    {
        intakeAssembly.main_intake_motor.spin(reverse, 12, volt);
        intakeAssembly.color_sense_motor.spin(reverse, 12, volt);
        intakeAssembly.front_intake_motor.spin(reverse, 12, volt);
    }
}
void scraper_mech(int hump)
{
    hook.toggle();
    intakeAssembly.main_intake_motor.spin(forward, 12, volt);
    intakeAssembly.color_sense_motor.spin(forward, 12, volt);
    intakeAssembly.front_intake_motor.spin(forward, 12, volt);
    chassis.drive_distance(hump, {.max_voltage = 6});
    chassis.drive_distance(-hump, {.max_voltage = 6});
    chassis.drive_distance(hump, {.max_voltage = 6});
    chassis.drive_distance(-hump, {.max_voltage = 6});
}

void stopping(void)
{
    intakeAssembly.main_intake_motor.stop(brake);
    intakeAssembly.color_sense_motor.stop(brake);
    intakeAssembly.front_intake_motor.stop(brake);
}
void odom_constants(void) {
    default_constants();
    chassis.heading_max_voltage = 10;
    chassis.turn_min_voltage = 3;
    chassis.drive_max_voltage = 8;
    chassis.drive_settle_error = 3;
    chassis.boomerang_lead = .5;
    chassis.boomerang_setback = 2;
    chassis.set_turn_constants(12, .258, .004, 2.196, 45);
    chassis.set_drive_constants(12, 1.2, 0.09, 7.7, 3);
    chassis.set_heading_constants(6, .3, .1, 3, 0);
    chassis.set_swing_constants(12, .337, .0095, 3.486, 45);

    // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_turn_exit_conditions(1.5, 75, 2000);
    chassis.set_drive_exit_conditions(1, 75, 3000);
    chassis.set_swing_exit_conditions(1.25, 75, 3000);
}

std::string template_auto(bool calibrate, auto_variation var, bool get_name) {
    /* The first variation will be this auto */
    if (var == one) {}

    /* We declare and allow a second variation of this auto; 
    You may want this if you want a different movements in the same starting configuration */
    if (var == two) { return template_auto_other_variation(calibrate, get_name); }

    if (get_name) { /* Give a desciption of your auto */ return "template auto 1 (3 objs)"; }
    if (calibrate) {
        /* Initialize robots starting position "https://path.jerryio.com/" and/or add extra movements to line up robots 
        starting position **IF MOVING DURING CALIBRATION DO BEFORE FIELD CONTROLLER PLUG IN** */
        chassis.set_coordinates(57.34, -16.506, 0);
    
        /* Example of turning before auto is ran */
        //chassis.turn_max_voltage = 6; 
        //chassis.turn_to_angle(45);

        return "";
    }
    
    /* We now run the auto */ 
    chassis.drive_distance(10);
    chassis.drive_distance(-10);

    return "";
}
std::string template_auto_other_variation(bool calibrate, bool get_name) {
    // Mirror template_auto() from the x-axis
    chassis.mirror_all_auton_y_pos();

    if (get_name) { return "template auto 2 (4 objs)"; }
    if (calibrate) {
        // Coordinates will be set to (55, -23.5) as y_pos is mirrored
        template_auto(calibrate, one, get_name);
        return "";
    }
    
    // Run auto, make sure to pass in one as var.
    template_auto(calibrate, one, get_name);

    return "";
}


std::string blue_left_winpoint(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "blue left winpoint"; }
    if (calibrate) {
        //chassis.set_coordinates(29.039,-47.338, 90);
        chassis.set_coordinates(53.99, -16.374, 180); //try 180 later when testing
        return "";
    }
    odom_constants();
    chassis.drive_to_point(53.99,-47.338,{.max_voltage = 6});
    chassis.turn_to_point(62.702,-47.338);
    scraper.toggle();
    scraper_mech(5);
    stopping();
    scraper.toggle();
    chassis.drive_to_point(29.039,-47.338);
    unload(3);
    wait(3,sec);
    stopping();
    chassis.drive_to_point(38.61,-47.338);
    chassis.turn_to_point(22.545,-22.729);
    load();
    chassis.drive_to_point(22.545,-22.729, {.max_voltage = 6});
    stopping();
    chassis.turn_to_point(10.241,-10.425,{.angle_offset = 180});
    chassis.drive_to_point(10.241,-10.425);
    unload(2);
    wait(2,sec);
    return "";
}
std::string blue_left_sawp(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "blue left sawp"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}
std::string blue_left_elim(bool calibrate, auto_variation var, bool get_name) {   
    if (get_name) { return "blue left elim"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}
std::string blue_right_winpoint(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "blue right winpoint"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }


    return "";
}
std::string blue_right_sawp(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "blue right sawp"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}
std::string blue_right_elim(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "blue right elim"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}

std::string red_left_winpoint(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "red left winpoint"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }
    
    return "";
}
std::string red_left_sawp(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "red left sawp"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}
std::string red_left_elim(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "red left elim"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);
        
        return "";
    }
    
    return "";
}
std::string red_right_winpoint(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "red right winpoint"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);
        return "";
    }

    return "";
}
std::string red_right_sawp(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "red right sawp"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);
        
        return "";
    }

    return "";
}
std::string red_right_elim(bool calibrate, auto_variation var, bool get_name) {   
    if (get_name) { return "red right elim"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}

std::string skills(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "skills"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}