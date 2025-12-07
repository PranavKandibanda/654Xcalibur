#include "vex.h"

using namespace vex;
using namespace mik;

std::string blue_right_winpoint(bool calibrate, mik::auto_variation var, bool get_name) {
    if (get_name) { return "blue right winpoint(4+3)"; }
    if (calibrate) {
        chassis.set_coordinates(62.155, 16.193, 270);
        return "";
    }
    // Path
    odom_constants();
    if (get_name) { return "blue left winpoint"; }

    // mirror here 
    if (calibrate) {
        chassis.set_coordinates(62.093, 16.308, 270);
        return "";
    }
    // Path
    odom_constants();
    chassis.drive_distance(17.748);
    chassis.turn_to_angle(0);
    chassis.drive_distance(29.5);
    chassis.turn_to_angle(90, {.turn_direction = cw});
    scraper.set(true);
    vex::task::sleep(100);
    intake_forward();
    chassis.drive_distance(20.456,{.min_voltage=8});
    vex::task::sleep(1000);
    intake_stop();
    chassis.drive_distance(-10,{.min_voltage = 8});
    scraper.set(false);
    chassis.drive_distance(-1);
    scraper.set(true);
    vex::task::sleep(500);
    scraper.set(false);
    chassis.turn_to_angle(270);
    chassis.drive_distance(19.1);
    score();
    vex::task::sleep(2000);
    intake_stop();

    chassis.drive_max_voltage = 10;
    chassis.turn_max_voltage = 12;
    chassis.heading_max_voltage = 6;
    chassis.swing_max_voltage = 12;

    chassis.reset_axis(left_sensor,bottom_wall,0);
    chassis.reset_axis(rear_sensor,right_wall,0);
    
    chassis.right_swing_to_angle(225,{.turn_direction = ccw});
    intake_forward();
    chassis.drive_distance(25,{.max_voltage = 3});
    scraper.set(true);
    chassis.turn_to_angle(215);
    chassis.drive_distance(20,{.wait = false});
    scraper.set(false);
    changePiston.set(false);
    chassis.wait();
    intakeAssembly.outake_motor.spin(reverse, 100, percent);
    vex::task::sleep(100);
    intake_reverse();
    vex::task::sleep(1000);
    /*chassis.drive_distance(15.748);
    chassis.turn_to_angle(180);
    chassis.drive_distance(30.037);
    chassis.turn_to_angle(90);
    scraper.set(true);
    vex::task::sleep(300);
    intake_forward();
    chassis.drive_distance(15.456);
    chassis.drive_distance(-5);
    chassis.turn_to_angle(270);
    chassis.drive_distance(34.1);
    score();
    vex::task::sleep(1500);
    intake_stop();*/


    /*chassis.turn_to_point(46.005, 15.897);
    chassis.drive_to_point(46.005, 15.897,{.max_voltage = 10});

    chassis.turn_to_point(46.005,46.863);
    chassis.drive_to_point(46.005,46.863);

    chassis.turn_to_point(61.162,46.884);
    scraper.set(true);
    task::sleep(200);
    chassis.drive_to_point(61.162, 46.884);
    intake_forward();
    task::sleep(3500);
    intake_stop();

    chassis.drive_distance(-5);
    scraper.set(false);
    task::sleep(100);

    //long goal score start
    chassis.turn_to_point(27.984, 46.612);
    chassis.drive_to_point(27.984, 46.612);
    
    score();
    task::sleep(1500);
    intake_stop();
    //long goal score end

    chassis.reset_axis(rear_sensor,right_wall,3.5);
    chassis.reset_axis(right_sensor,top_wall,4);

    chassis.drive_distance(-5);
    hook.set(true);
    chassis.turn_to_point(36.785, 37.582,{.turn_direction= ccw});
    chassis.drive_to_point(36.785, 37.582);

    chassis.turn_to_point(11.312, 37.582,{.angle_offset=180}); //tune this point for hook to go in goal
    chassis.drive_to_point(11.312, 37.582, {.min_voltage = 8});*/
    return "";
}
