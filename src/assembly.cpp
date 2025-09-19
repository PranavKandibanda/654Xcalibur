#include "vex.h"

using namespace vex;

// Pass in the devices we want to use
Assembly::Assembly(
    mik::motor_group intake,
    mik::motor main_intake_motor, 
    mik::motor color_sense_motor,
    mik::motor front_intake_motor
) :
    // Assign the ports to the devices
    intake(intake),
    main_intake_motor(main_intake_motor),
    color_sense_motor(color_sense_motor),
    front_intake_motor(front_intake_motor)
{}

// You want to call this function once in the user control function in main.
void Assembly::init() {
    
} 

// You want to put this function inside the user control loop in main.
void Assembly::control() {
    intake_motors_control();
    //long_piston_control();
}



/*void Assembly::lift_arm_control() {
    // new_press macro only allows input to go through when button is pressed. Resets after button is released.
    if (btnX_new_press(Controller.ButtonX.pressing())) {
        // If Up arrow is pressed it will swap lift positions between scoring and loading
        if (lift_arm_position != SCORING) {
            lift_arm_position = SCORING; // Lift task will read this value
        } else {
            lift_arm_position = LOADING;
        }
    } else if (btnUp_new_press(Controller.ButtonUp.pressing())) {
        // If Up arrow is pressed it will swap lift positions between loading and idle
        if (lift_arm_position != LOADING) {
            lift_arm_position = LOADING;
        } else {
            lift_arm_position = IDLE;
        }
    }
}*/

// Spins intake forward if L1 is being held, reverse if L2 is being held; stops otherwise
void Assembly::intake_motors_control() {
    if (Controller.ButtonL1.pressing()) {
        main_intake_motor.spin(reverse, 12, volt);
        color_sense_motor.spin(reverse, 12, volt);
        front_intake_motor.spin(reverse, 12, volt);
    } 
    else if (Controller.ButtonL2.pressing()) {
        main_intake_motor.spin(forward, 12, volt);
        color_sense_motor.spin(forward, 12, volt);
        front_intake_motor.spin(forward, 12, volt);
    }
    else {
        intake.stop(brake);
        main_intake_motor.stop(brake);
        color_sense_motor.stop(brake);
        front_intake_motor.stop(brake);
    }
}