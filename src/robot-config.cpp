#include "vex.h"
#include "PistonAssembly.h"
using namespace vex;
using namespace mik;

vex::brain Brain;
vex::controller Controller;
vex::competition Competition;

bool calibrating = false;

// Allows recalibration of the inertial using MINIMUN_INERTIAL_CALIBRATION_ERROR
bool force_calibrate_inertial = false;

// After inertial sensor calibration the program waits 1 second and checks 
// to see if the angle has changed more than this value. If so, it will recalibrate 
// the inertial sensor and vibrate the controller. The lower the value the less likelihood
// of a failed calibration.
static const float MINIMUN_INERTIAL_CALIBRATION_ERROR = .05;
//USED PORTS: 1,3,4,5,6,7,8,9,12,15,18,19
Chassis chassis(
	// Drivetrain motors
	mik::motor_group({
		mik::motor(PORT4, true, blue_6_1, "left_front_motor"), 
		mik::motor(PORT5, true, blue_6_1, "left_middle_motor"), 
		mik::motor(PORT6, true, blue_6_1, "left_back_motor")
	}),
	mik::motor_group({
		mik::motor(PORT1, false, blue_6_1, "right_front_motor"), 
		mik::motor(PORT12, false, blue_6_1, "right_middle_motor"), 
		mik::motor(PORT3, false, blue_6_1, "right_back_motor")
	}),

	PORT18, // Inertia sensor port
	360,    // Inertial scale

	PORT20, // Forward tracker port
	-2,     // Forward tracker wheel diameter
	0,      // Forward tracker center distance

	PORT15, // Sideways tracker port
	2,      // Sideways tracker wheel diameter
	0.3,    // Sideways tracker center distance

	// Distance sensors (currently none installed)tssax
	//     // by 5 inches to the right and 3.5 inches forward from the tracking center 
	//     mik::distance(PORT17, rear_sensor, 5, 3.5)
	// })
	mik::distance_reset({})
);

IntakeAssembly intakeAssembly(
	mik::motor_group({
		mik::motor(PORT9, true, green_18_1, "main_intake_motor"),
		mik::motor(PORT8,  false, green_18_1, "color_sense_motor"),
		mik::motor(PORT7,  true, green_18_1, "front_intake_motor")
	}),
	mik::motor(PORT9, false, green_18_1, "main_intake_motor"),
	mik::motor(PORT8,  true, green_18_1, "color_sense_motor"),
	mik::motor(PORT7,  false, green_18_1, "front_intake_motor"),
	vex::optical(PORT19)
);

// Create pistons first
mik::piston park_piston(PORT_C, false);
mik::piston hook_piston(PORT_A, false);
mik::piston scraper_piston(PORT_B, false);

// Create assemblies with piston references
ParkAssembly park(park_piston);
HookAssembly hook(hook_piston);
ScraperAssembly scraper(scraper_piston);
/** Allows UI to display all motor values */
void log_motors() {
    config_add_motors({
		// Add all mik motor groups in here
		chassis.left_drive, 
		chassis.right_drive, 
    }, 
	{
		// Add all mik motors in here
		intakeAssembly.main_intake_motor,
		intakeAssembly.color_sense_motor,
		intakeAssembly.front_intake_motor
    }
  );
}

void calibrate_inertial(void) {
	calibrating = true;
	chassis.inertial.calibrate();
  
	while (chassis.inertial.isCalibrating()) {
		vex::task::sleep(25);
	}
  
  	// Recalibrate inertial until it is within calibration threshold
  	float starting_rotation = chassis.inertial.rotation();
  	task::sleep(1000);
	if (force_calibrate_inertial && std::abs(chassis.inertial.rotation() - starting_rotation) > MINIMUN_INERTIAL_CALIBRATION_ERROR) { 
		Controller.rumble("-");
		calibrate_inertial();
  	}
  	calibrating = false;
}

static void loading_screen(bool stop) {
	static vex::task loading_bar;
	
	if (stop) {
		loading_bar.stop();
		return;
	}

	Controller.Screen.setCursor(1, 1);
	Brain.Screen.drawImageFromBuffer(mikLib_logo, 0, 0, sizeof(mikLib_logo));
	
	loading_bar = vex::task([](){
		std::string calibrate = "Calibrating";
		Brain.Screen.setFillColor("#3d3d3d");
		int count = 0;
		while(1) {
			Brain.Screen.printAt(184, 220, calibrate.c_str());
			Controller.Screen.setCursor(1, 1);
			Controller.Screen.print((calibrate).c_str());
			task::sleep(200);
			calibrate.append(".");
			count++;
			if (count > 4) {
				count = 0;
				calibrate = "Calibrating";
				Brain.Screen.printAt(184, 220, (calibrate + "     ").c_str());
				Controller.Screen.setCursor(1, 1);
				Controller.Screen.print((calibrate + "     ").c_str());
			}
		}
		return 0;
	});
}

static void handle_disconnected_devices() {
	int errors = run_diagnostic(); 
	if (errors > 0) {
		Controller.rumble(".");
		Controller.Screen.setCursor(1, 1);
		Controller.Screen.print((to_string(errors) + " ERRORS DETECTED").c_str());
		Controller.Screen.setCursor(2, 1);
		Controller.Screen.print("[Config]->[Error Data]");
		task::sleep(500);
	}
}

static void reset_screens() {
	Brain.Screen.clearScreen();
	Controller.Screen.setCursor(1, 1);
	Controller.Screen.print("                                  ");
	Brain.Screen.setCursor(1,1);
	vex::task::sleep(50);
	Brain.Screen.clearScreen();
	Brain.Screen.setFillColor(vex::color::black);
	Brain.Screen.setPenWidth(1);
	Brain.Screen.setPenColor(vex::color::white);
}

void init(void) {
	// Start loading screen
	loading_screen(false);

	// Setup motors
	log_motors();

	// Calibrate inertial
	calibrate_inertial();

	// Stop loading screen
	loading_screen(true);

	// Check disconnected devices
	handle_disconnected_devices();

	// Init brain and controller screen
	reset_screens();

	// Make sure user control is enabled
	enable_user_control();
}

static bool user_control_disabled = false;

void disable_user_control(bool stop_all_motors_) {
	user_control_disabled = true;
	if (stop_all_motors_) {
		stop_all_motors(vex::brakeType::hold);
		set_brake_all_motors(vex::brakeType::coast);
	}
}

void enable_user_control(void) {
  	user_control_disabled = false;
}

bool control_disabled(void) {
  	return user_control_disabled;
}