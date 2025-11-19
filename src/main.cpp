#include "vex.h"
#include "PistonAssembly.h"
#include "mikLib/globals.h"

using namespace vex;
using namespace mik;


task UI;

static int run_UI() {
    UI_init();
    UI_controller_auton_selector();
    UI_render();
    return 0;
}

void pre_auton() {
    init();
    default_constants();
    //chassis.forward_tracker.setReversed(true);
    UI = task(run_UI);
}

void auton(void) {
    UI.stop();
    auton_scr->start_auton();
}

void user_control(void) {
    while (calibrating) { task::sleep(50); }

    // How you want your drivetrain to stop during driver
    chassis.set_brake_type(brakeType::coast);
    intakeAssembly.init();
    static bool lastR1 = false, lastR2 = false, lastUp = false, lastRight = false;
    while (true) {
        if (!control_disabled()) {
            chassis.control(drive_mode::SPLIT_ARCADE);
            intakeAssembly.control();
            //Toggle hook with R1
            bool r1 = Controller.ButtonR1.pressing();
            if (r1 && !lastR1)
            {
                hook.toggle();
            }
            lastR1 = r1;

            // Toggle scraper with R2
            bool r2 = Controller.ButtonR2.pressing();
            if (r2 && !lastR2)
            {
                scraper.toggle();
            }
            lastR2 = r2;

            // Toggle park with right
            bool right = Controller.ButtonRight.pressing();
            if (right && !lastRight)
            {
                park.toggle();
            }
            lastRight = right;

            //Toggle level change with button up
            bool up = Controller.ButtonUp.pressing();
            if (up && !lastUp)
            {
                changePiston.toggle();
            }
            lastUp = up;
        }
        task::sleep(5);
    }
}

int main() {
    Competition.autonomous(auton);
    Competition.drivercontrol(user_control);

    pre_auton();

    while (true) {
        task::sleep(100);
    }
}
