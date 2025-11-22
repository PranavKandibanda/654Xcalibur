#include "vex.h"

using namespace vex;
using namespace mik;

std::string blue_right_winpoint(bool calibrate, mik::auto_variation var, bool get_name) {
    if (get_name) { return "blue right winpoint(4+3)"; }
    if (calibrate) {
        chassis.set_coordinates(46.928, 14.266, 360);
        return "";
    }
    // Path
    odom_constants();
    chassis.drive_to_point(47.22, 43.928,{.max_voltage = 10});

    chassis.turn_to_point(60, 41.5);
    scraper.set(true);
    task::sleep(200);
    chassis.drive_to_point(64.5, 41);
    intake_forward();
    task::sleep(3500);
    intake_stop();

    chassis.drive_distance(-5);
    scraper.set(false);
    task::sleep(100);
    chassis.turn_to_point(25.984, 42);
    chassis.drive_to_point(25.984, 42);
    
    score();
    task::sleep(1500);
    intake_stop();

    /*chassis.turn_to_point(47.22, 46.928);
    chassis.drive_to_point(47.22, 46.928);
    score();
    wait(500,msec);
    intake_stop();*/

    /*
    chassis.drive_to_point(36.822, -46.612);

    chassis.turn_to_point(36.785, -37.582);
    chassis.drive_to_point(36.785, -37.582);
    hook.set(true);

    chassis.turn_to_point(11.312, -37.582);
    chassis.drive_to_point(11.312, -37.582);
    */
    return "";
}
