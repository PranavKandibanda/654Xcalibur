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
    void color_sort();
    void long_piston_control();

    // Configuration
    bool enable_sorting = true;      // Can be toggled off to treat all game objects the same
    bool enable_debug   = false;     // When true, prints sensor info periodically
    int  prox_threshold = 40;        // Minimum proximity to consider an object present
    int  brightness_threshold = 25;  // Fallback brightness threshold if proximity unreliable

    // Timing helpers
    uint32_t last_debug_time = 0;
    uint32_t debug_interval_ms = 250; // Throttle debug prints

    // Debug samples (read-only for other code if needed)
    double last_hue = 0;
    int    last_prox = 0;
    bool   last_is_item_red = false;
    bool   last_is_item_blue = false;
    bool   last_reject = false;

    mik::motor_group intake;
    mik::motor main_intake_motor;
    mik::motor color_sense_motor;
    mik::motor front_intake_motor;
    vex::optical color_sensor;
};
