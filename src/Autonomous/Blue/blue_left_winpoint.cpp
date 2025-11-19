#include "vex.h"

using namespace vex;
using namespace mik;

std::string blue_left_winpoint(bool calibrate, mik::auto_variation var, bool get_name) {
    if (get_name) { return "blue left winpoint"; }
    if (calibrate) {
        chassis.set_coordinates(46.928, -14.266, 180.054);
        return "";
    }
    //
    chassis.turn_to_point(47.22, -46.928);
    chassis.drive_to_point(47.22, -46.928);
    scraper.set(true);
    intake_forward();
    //set up scraper and position for loader

    //
    chassis.turn_to_point(61.162, -46.884);
    chassis.drive_to_point(61.162, -46.884);
    wait(500,msec);
    intake_stop();
    //scraper inserted and balls from loader collected

    //
    chassis.drive_distance(-5,{.max_voltage = 5});
    scraper.set(false);
    changePiston.set(true);
    //taking some distance as to not hit the loader while turning.

    //
    chassis.turn_to_point(27.984, -46.612);
    chassis.drive_to_point(27.984, -46.612);
    score();
    wait(500,msec);
    intake_stop();
    //scored long goal

    //
    chassis.drive_to_point(36.822, -46.612);
    chassis.turn_to_point(36.785, -37.582);
    chassis.drive_to_point(36.785, -37.582);
    hook.set(true);
    //aligned beside goal

    //Putting that ball in the control zone !!!!!!
    chassis.turn_to_point(11.312, -37.582);
    chassis.drive_to_point(11.312, -37.582, {.min_voltage = 3});
    return "";
}