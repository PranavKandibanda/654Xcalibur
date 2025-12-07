#include "vex.h"

using namespace vex;
using namespace mik;

std::string red_left_winpoint(bool calibrate, mik::auto_variation var, bool get_name) { 
    if (get_name) { return "red left winpoint"; }

    // mirror here 
    if (calibrate) {
        chassis.set_coordinates(-62.093, 16.308, 90);
        return "";
    }
    // Path
    chassis.drive_max_voltage = 12;
    chassis.turn_max_voltage = 12;
    chassis.heading_max_voltage = 6;
    chassis.swing_max_voltage = 12;

    odom_constants();
    chassis.drive_distance(15.748,{.min_voltage = 6});
    chassis.turn_to_angle(0);
    chassis.drive_distance(30.8,{.min_voltage = 6});
    chassis.turn_to_angle(272,{.max_voltage = 9});
    scraper.set(true);
    vex::task::sleep(300);
    intake_forward();
    chassis.drive_distance(10.656);
    scraper.set(false);
    vex::task::sleep(3000);
    intake_stop();
    chassis.drive_distance(-10);
    intake_reverse();
    vex::task::sleep(300);
    intake_stop();
    chassis.turn_to_angle(93,{.max_voltage=7});
    chassis.drive_distance(18.1);
    score();
    vex::task::sleep(2000);
    intake_stop();

    chassis.reset_axis(left_sensor,bottom_wall,0);
    chassis.reset_axis(rear_sensor,right_wall,0);
    
    chassis.right_swing_to_angle(155,{.turn_direction = cw});
    intake_forward();
    chassis.drive_distance(25,{.max_voltage = 3});
    scraper.set(true);
    chassis.turn_to_angle(139);
    chassis.drive_distance(15,{.wait = false,.min_voltage = 3});
    scraper.set(false);
    changePiston.set(false);
    chassis.wait();
    intakeAssembly.outake_motor.spin(reverse, 100, percent);
    vex::task::sleep(100);
    intakeAssembly.outake_motor.stop(coast);
    score();
    vex::task::sleep(1000);
    /*chassis.turn_to_point(-46.345, -16.308);
    chassis.drive_to_point(46.345, -16.308,{.max_voltage = 10});

    chassis.turn_to_point(-45.345, -50.345);
    chassis.drive_to_point(-45.345, -50.345);
    scraper.set(true);
    task::sleep(200); //waiting for scraper to come down
    chassis.turn_to_point(-62.093, -50.345);
    chassis.drive_distance(-19.456,{.max_voltage = 6}); // tune this amount down slowly
    intake_forward();
    vex::task::sleep(1100);
    intake_stop();
    scraper.set(false);
    vex::task::sleep(100);
    scraper.set(true);
    vex::task::sleep(100);
    scraper.set(false);
    chassis.drive_distance(-5,{.min_voltage = 8});//moving back to provide space for scraper to come up
    chassis.turn_to_point(-27.984, -44);
    chassis.drive_to_point(-27.984, -44);
    
    score();
    task::sleep(1500);
    intake_stop();

    chassis.reset_axis(left_sensor,bottom_wall,0);
    chassis.reset_axis(rear_sensor,right_wall,0);
    
    chassis.right_swing_to_angle(155,{.turn_direction = cw});
    intake_forward();
    chassis.drive_distance(25,{.max_voltage = 3});
    scraper.set(true);
    chassis.turn_to_angle(135);
    chassis.drive_distance(10);*/
    return "";
}