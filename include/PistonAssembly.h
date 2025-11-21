#pragma once
#include "vex.h"
using namespace vex;

class PistonAssembly {
public:
    PistonAssembly(mik::piston& solenoid1);

    void toggle();
    void set(bool state);

    mik::piston& solenoid1;
    bool extended = false;
};

// Type aliases for clarity
using ParkAssembly = PistonAssembly;
using HookAssembly = PistonAssembly;
using ScraperAssembly = PistonAssembly;