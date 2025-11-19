#include "vex.h"

using namespace vex;
using namespace mik;

void intake_forward(void)
{
    intakeAssembly.main_intake_motor.spin(forward, 100, percent);
    intakeAssembly.front_intake_motor.spin(forward, 100, percent);
    if (intakeAssembly.ball_sensor.objectDistance(inches) < 1.5) {
        intakeAssembly.outake_motor.stop(brake);
    } else {
        intakeAssembly.outake_motor.spin(forward, 100, percent);
    }
}

void intake_reverse(void)
{
    intakeAssembly.main_intake_motor.spin(reverse, 100, percent);
    intakeAssembly.front_intake_motor.spin(reverse, 100, percent);
    intakeAssembly.outake_motor.spin(reverse, 100, percent);
}

void intake_stop(void)
{
    intakeAssembly.main_intake_motor.stop(brake);
    intakeAssembly.front_intake_motor.stop(brake);
    intakeAssembly.outake_motor.stop(brake);
}

void score(void)
{
    intakeAssembly.outake_motor.spin(forward, 100, percent);
    intakeAssembly.main_intake_motor.spin(forward, 100, percent);
    intakeAssembly.front_intake_motor.spin(forward, 100, percent);
}