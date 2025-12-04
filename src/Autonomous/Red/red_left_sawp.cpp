#include "vex.h"

using namespace vex;
using namespace mik;

std::string red_left_sawp(bool calibrate, mik::auto_variation var, bool get_name) { 
    if (get_name) { return "red sawp"; }
    if (calibrate) {
        chassis.set_coordinates(-53.927, -17.474, 180.299);
        return "";
    }

    chassis.turn_to_point(-53.773, -47.008);
    chassis.drive_to_point(-53.773, -47.008,{.max_voltage = 10});

    scraper.set(true);
    task::sleep(200);

    chassis.drive_distance(5);
    intake_forward();
    task::sleep(2500);
    intake_stop();

    chassis.drive_distance(-5);
    scraper.set(false);
    task::sleep(100); //waiting for scraper to retract

    chassis.turn_to_point(-30.385, -47.201);
    chassis.drive_to_point(-30.385, -47.201);
    score();
    task::sleep(1500);
    intake_stop();
    chassis.reset_axis(rear_sensor,left_wall,4);
    chassis.reset_axis(left_sensor,top_wall,3.5);

    chassis.drive_distance(-6.76);

    chassis.turn_to_point(-27.486, -30.385);
    chassis.drive_to_point(-27.486, -30.385);

    intake_forward();
    chassis.turn_to_point(-18.401,-17.241);
    chassis.drive_to_point(-18.401,-17.241,{.max_voltage = 4});
    intake_stop();

    chassis.turn_to_point(-12.602,-12.023);
    chassis.drive_to_point(-12.602,-12.023);
    changePiston.set(false);
    score();
    task::sleep(1500);
    intake_stop();

    chassis.turn_to_point(-34.637,-11.829);
    chassis.drive_to_point(-34.637,-11.829,{.min_voltage = 6, .max_voltage = 12});

    chassis.turn_to_point(-33.513,46.683);
    changePiston.set(true);
    chassis.drive_to_point(-33.513,46.683,{.min_voltage = 6, .max_voltage = 12});

    chassis.turn_to_angle(270);
    chassis.drive_distance(2,{.max_voltage = 2});
    
    score();
    return "";
}