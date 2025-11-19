#pragma once
#include "vex.h"
using namespace vex;

class IntakeAssembly {
public:
    IntakeAssembly(
        mik::motor_group intake,
        mik::motor main_intake_motor, 
        mik::motor outake_motor,
        mik::motor front_intake_motor,
        mik::distance ball_sensor
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
    mik::distance ball_sensor;
    // When true: keep outake motor moving even when ball is detected.
    // When false: stop (brake) outake motor when ball is detected.
    bool l1_keep_moving = false;
    // Used to detect button-edge for toggling the above flag.
    bool prev_button_l1 = true;
};
