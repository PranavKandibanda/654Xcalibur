#include "vex.h"

using namespace vex;
using namespace mik;

std::string skills(bool calibrate, mik::auto_variation var, bool get_name) {
    if (get_name) { return "skills"; }
    if (calibrate) {
        chassis.set_coordinates(-54.5, 0, 270);

        return "";
    }

    return "";
}