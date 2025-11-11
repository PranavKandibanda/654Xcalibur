#pragma once
#include "vex.h"
using namespace vex;

class IntakeAssembly {
public:
    IntakeAssembly(
        mik::motor_group intake,
        mik::motor main_intake_motor, 
        mik::motor outake_motor,
        mik::motor front_intake_motor
    );
    
    void init();
    void control();

    void intake_motors_control();
    void color_sort(bool reverse_sort = false);
    void color_sort_tech(bool reverse_sort = false,bool hook_mech = false);
    void skills_control();

    mik::motor_group intake;
    mik::motor main_intake_motor;
    mik::motor outake_motor;
    mik::motor front_intake_motor;
};
