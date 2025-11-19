#include "vex.h"

using namespace vex;
using namespace mik;

void default_constants(void) {
	chassis.set_control_constants(5, 10, 1.019, 5, 10, 1.019);

    // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
    chassis.set_turn_constants(12, .258, .004, 2.196, 45);
    chassis.set_drive_constants(12, 1.2, 0.03, 7.7, 3);
    chassis.set_heading_constants(6, .3, .1, 3, 0);
    chassis.set_swing_constants(12, .337, .0095, 3.486, 45);

    // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_turn_exit_conditions(1, 300, 3000);
    chassis.set_drive_exit_conditions(3, 100, 5000);
    chassis.set_swing_exit_conditions(1, 300, 3000);
}

void odom_constants(void) {
	default_constants();
	default_constants();
    chassis.heading_max_voltage = 10;
    chassis.turn_min_voltage = 3;
    chassis.drive_max_voltage = 8;
    chassis.drive_settle_error = 3;
    chassis.boomerang_lead = .5;
    chassis.boomerang_setback = 2;
    chassis.set_turn_constants(12, .258, .004, 2.196, 45);
    chassis.set_drive_constants(12, 1.2, 0.083, 7.7, 3);
    chassis.set_heading_constants(6, .3, .1, 3, 0);
    chassis.set_swing_constants(12, .337, .0095, 3.486, 45);

    // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_drive_exit_conditions(1, 75, 3000);
    chassis.set_turn_exit_conditions(1.5, 75, 2000);
    chassis.set_swing_exit_conditions(1.25, 75, 3000);
}

void mogo_constants() {
	odom_constants();
	mogo_offsets();

	chassis.set_turn_constants(12, .437, 0.02, 3.7, 15);
	chassis.set_turn_exit_conditions(.1, 300, 3000);
	}

void mogo_offsets() {
  	chassis.set_tracking_offsets(0, 1);
}