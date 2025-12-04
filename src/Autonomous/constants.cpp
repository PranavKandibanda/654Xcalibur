#include "vex.h"

using namespace vex;
using namespace mik;

void default_constants(void) {
    chassis.set_control_constants(5, 10, 1.019, 5, 10, 1.019);

    chassis.set_turn_constants(12,.304, .005, 4.026, 15);
    chassis.set_drive_constants(10, 1.5, 0, 8.8, 0);
    chassis.set_heading_constants(6, .4, 0, 1, 0);
    chassis.set_swing_constants(12, .437, .0295, 3.486, 15);

    chassis.set_turn_exit_conditions(3,300,1000);//can reduce to 1000 to speed up if needed
    chassis.set_drive_exit_conditions(3,300,3000);
    chassis.set_swing_exit_conditions(3,300,3000);
}

void odom_constants(void) {
	default_constants();
    /*chassis.heading_max_voltage = 10;
    chassis.drive_max_voltage = 8;
    chassis.drive_settle_error = 3;
    chassis.boomerang_lead = .5;
    chassis.boomerang_setback = 2;*/
}

void mogo_constants() {
	odom_constants();
	mogo_offsets();

    chassis.set_turn_exit_conditions(1,300,1000);
	chassis.set_drive_exit_conditions(3,150,2000);
	chassis.set_heading_constants(6, .3, .1, 3, 0);
	chassis.set_swing_exit_conditions(1,300,1500);
	}

void mogo_offsets() {
  	chassis.set_tracking_offsets(0, 1);
}