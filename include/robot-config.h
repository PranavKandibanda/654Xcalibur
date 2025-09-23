#include "vex.h"
class motor;
class motor_group;
class IntakeAssembly;
class PistonAssembly;
using ParkAssembly = PistonAssembly;
using HookAssembly = PistonAssembly;
using ScraperAssembly = PistonAssembly;

extern vex::brain Brain;
extern vex::controller Controller;
extern vex::competition Competition;

extern bool calibrating;
extern bool force_calibrate_inertial;

extern IntakeAssembly intakeAssembly;
extern ParkAssembly park;
extern HookAssembly hook;
extern ScraperAssembly scraper;


void init(void);
void calibrate_inertial(void);

void disable_user_control(bool stop_all_motors_ = false);
void enable_user_control(void);
bool control_disabled(void);
