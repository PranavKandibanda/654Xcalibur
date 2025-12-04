#include "vex.h"

using namespace vex;
using namespace mik;

std::string blue_left_winpoint(bool calibrate, mik::auto_variation var, bool get_name) {
    if (get_name) { return "blue left winpoint"; }

    // mirror here 
    if (calibrate) {
        chassis.set_coordinates(62.093, -16.308, 270);
        return "";
    }
    // Path
    odom_constants();

    chassis.drive_max_voltage = 9;
    chassis.turn_max_voltage = 11;
    chassis.heading_max_voltage = 5;
    chassis.swing_max_voltage = 11;

    chassis.turn_to_point(46.345, -16.308);
    chassis.drive_to_point(46.345, -16.308,{.max_voltage = 8});

    chassis.turn_to_point(45.345, -50.345);
    chassis.drive_to_point(45.345, -50.345);
    scraper.set(true);
    task::sleep(200); //waiting for scraper to come down
    chassis.turn_to_point(62.093, -50.345);
    chassis.drive_distance(17.456,{.max_voltage = 6}); // tune this amount down slowly
    intake_forward();
    vex::task::sleep(1100);
    intake_stop();
    chassis.drive_distance(-5,{.max_voltage = 8});//moving back to provide space for scraper to come up
    scraper.set(false);
    vex::task::sleep(500);
    scraper.set(true);
    chassis.drive_distance(-1);
    vex::task::sleep(500);
    scraper.set(false);
    chassis.turn_to_point(27.984, -44);
    chassis.drive_to_point(27.984, -44);
    
    score();
    task::sleep(1500);
    intake_stop();

    chassis.drive_max_voltage = 10;
    chassis.turn_max_voltage = 12;
    chassis.heading_max_voltage = 6;
    chassis.swing_max_voltage = 12;

    chassis.reset_axis(left_sensor,bottom_wall,0);
    chassis.reset_axis(rear_sensor,right_wall,0);
    
    chassis.right_swing_to_angle(335,{.turn_direction = cw});
    intake_forward();
    chassis.drive_distance(25,{.max_voltage = 3});
    scraper.set(true);
    chassis.turn_to_angle(315);
    chassis.drive_distance(20,{.wait = false});
    scraper.set(false);
    chassis.wait();
    score();
    vex::task::sleep(1000);
    return "";
}