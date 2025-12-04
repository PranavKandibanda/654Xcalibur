#include "vex.h"

using namespace vex;
using namespace mik;

std::string red_right_winpoint(bool calibrate, mik::auto_variation var, bool get_name) { 
    if (get_name) { return "red right winpoint bread and butter"; }
    if (calibrate) {
        chassis.set_coordinates(-62.155, 16.193, 270);
        return "";
    }
    // Path
    odom_constants();
    chassis.turn_to_point(-46.005, 15.897);
    chassis.drive_to_point(-46.005, 15.897,{.max_voltage = 10});

    chassis.turn_to_point(-46.005,46.863);
    chassis.drive_to_point(-46.005,46.863);

    chassis.turn_to_point(-61.162,46.884);
    scraper.set(true);
    task::sleep(200);
    chassis.drive_to_point(-61.162, 46.884);
    intake_forward();
    task::sleep(3500);
    intake_stop();

    chassis.drive_distance(-5);
    scraper.set(false);
    task::sleep(100); //waiting for scraper to retract

    //long goal score start
    chassis.turn_to_point(-27.984, 46.612);
    chassis.drive_to_point(-27.984, 46.612);
    score();
    task::sleep(1500);
    intake_stop();
    //long goal score end

    chassis.reset_axis(rear_sensor,right_wall,3.5);
    chassis.reset_axis(right_sensor,top_wall,4);

    chassis.drive_distance(-5);
    hook.set(true);
    chassis.turn_to_point(-36.785, 37.582,{.turn_direction= ccw});
    chassis.drive_to_point(-36.785, 37.582);

    chassis.turn_to_point(-11.312, 37.582,{.angle_offset=180}); //tune this point for hook to go in goal
    chassis.drive_to_point(-11.312, 37.582, {.min_voltage = 8});

    
    return "";
}