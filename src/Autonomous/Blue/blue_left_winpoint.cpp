#include "vex.h"

using namespace vex;
using namespace mik;

std::string blue_left_winpoint(bool calibrate, mik::auto_variation var, bool get_name) {
    if (get_name) { return "blue left winpoint"; }
    if (calibrate) {
        chassis.set_coordinates(53.886, -17.385, 180.054);
        return "";
    }
    // Path
    chassis.turn_to_point(53.877, -26.959);
    chassis.drive_to_point(53.877, -26.959);

    chassis.turn_to_point(50.497, -46.884);
    chassis.drive_to_point(50.497, -46.884);
    scraper.set(true);
    intake_forward();

    chassis.turn_to_point(61.162, -46.884);
    chassis.drive_to_point(61.162, -46.884);
    wait(500,msec);
    intake_stop();

    chassis.drive_distance(-5);
    scraper.set(false);

    chassis.turn_to_point(27.984, -46.612);
    chassis.drive_to_point(27.984, -46.612);
    score();
    wait(500,msec);
    intake_stop();

    chassis.drive_to_point(36.822, -46.612);

    chassis.turn_to_point(36.785, -37.582);
    chassis.drive_to_point(36.785, -37.582);
    hook.set(true);

    chassis.turn_to_point(11.312, -37.582);
    chassis.drive_to_point(11.312, -37.582);
    return "";
}