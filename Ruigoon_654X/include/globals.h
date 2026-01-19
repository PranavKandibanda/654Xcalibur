#ifndef GLOBALS_H
#define GLOBALS_H

#include "api.h"
#include "lemlib/api.hpp"
#include "pros/adi.hpp"
#include "pros/motors.hpp"

// extern tells the compiler that these variables are defined elsewhere (in
// globals.cpp)
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;
extern pros::Controller controller;
extern pros::Imu imu;
extern lemlib::Drivetrain drivetrain;
extern lemlib::ControllerSettings linearController;
extern lemlib::ControllerSettings angularController;
extern lemlib::TrackingWheel horizontalEnc;
extern lemlib::TrackingWheel verticalEnc;
extern lemlib::OdomSensors sensors;
extern lemlib::ExpoDriveCurve throttleCurve;
extern lemlib::ExpoDriveCurve steerCurve;
extern lemlib::Chassis chassis;

extern pros::Distance dNorth;
extern pros::Distance dEast;
extern pros::Distance dSouth;
extern pros::Distance dWest;

constexpr int WALL_NORTH = 71;
constexpr int WALL_SOUTH = -71;
constexpr int X_offset = 6; //distance from center of robot to dist sensors (left/right)
constexpr int Y_offset = 8; //distance from center of robot to dist sensors (front/back)
#endif // GLOBALS_H