#pragma once

#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/imu.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "robodash/api.h"

// Extern declarations for hardware from main.cpp
extern lemlib::Chassis chassis;
extern pros::adi::Pneumatics hook_piston;
extern pros::adi::Pneumatics scraper_piston;
extern pros::adi::Pneumatics middle;
extern pros::Motor intake_stage1;
extern pros::Motor intake_stage2;

// Helper function declarations (if defined in main.cpp)
void intake();
void outtake();
void load();
void stop_load();

// Autonomous routine declarations
void skills();
void blue_5_3_auton_left();
void blue_3_3_auton_left();
void pid_test_linear();
void pid_test_angular();
void accuracy_tuning();