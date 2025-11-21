#include "PistonAssembly.h"
#include "vex.h"
PistonAssembly::PistonAssembly(mik::piston& solenoid1)
    : solenoid1(solenoid1) {}

void PistonAssembly::toggle() {
    extended = !extended;
    solenoid1.set(extended);
}

void PistonAssembly::set(bool state) {
    extended = state;
    solenoid1.set(extended);
}