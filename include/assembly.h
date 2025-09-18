#pragma once

#include "vex.h"

using namespace vex;

enum lift_positions : int { IDLE = 229, LOADING = 206, SCORING = 99 };

class Assembly {
public:
    Assembly(
        mik::motor_group intake,
        mik::motor main_intake_motor, 
        mik::motor color_sense_motor,
        mik::motor front_intake_motor
    );
    
    void init();
    void control();

    void intake_motors_control();
    void long_piston_control();

    
    mik::motor_group intake;
    mik::motor main_intake_motor;
    mik::motor color_sense_motor;
    mik::motor front_intake_motor;
};