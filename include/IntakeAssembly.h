#pragma once
#include "vex.h"
using namespace vex;

class IntakeAssembly {
public:
    IntakeAssembly(
        mik::motor_group intake,
        mik::motor main_intake_motor, 
        mik::motor color_sense_motor,
        mik::motor front_intake_motor,
        vex::optical color_sensor
    );
    
    void init();
    void control();

    void intake_motors_control();
    void long_piston_control();

    mik::motor_group intake;
    mik::motor main_intake_motor;
    mik::motor color_sense_motor;
    mik::motor front_intake_motor;
    vex::optical color_sensor;
};
