#include "lemlib/asset.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/rtos.hpp"
#include <future>
#include "autons.h"
//ASSET(testSum_txt);

void skills()
{
}

void left_5_3_auton() //unifinished, moving onto 3+3 push
{
    hook_piston.set_value(false);
    scraper_piston.set_value(false);
    middle.set_value(false);
    chassis.setPose(49.554,-15.874,270);
    scraper_piston.set_value(false);
    hook_piston.set_value(false);

    chassis.moveToPoint(44.554,-15.874, 400);

    load();
    chassis.turnToPoint(32.468,-18.643,200);
    chassis.moveToPoint(32.468,-18.643,400);

    
    chassis.moveToPose(5.63, -52.745,206.4,3000,{});
    
    // @TODO run intake code here
    chassis.waitUntil(5);
    scraper_piston.set_value(true);
    pros::delay(300);
    chassis.waitUntil(13);
    scraper_piston.set_value(false);
    pros::delay(300);

    chassis.waitUntil(50);
    scraper_piston.set_value(true);
    chassis.waitUntilDone();
    pros::delay(300);
    stop_load();
    chassis.waitUntilDone();
    // @TODO stop intake code here

    chassis.moveToPose(23.05, -23.582, 320.1, 200,{.forwards = false},false);
    chassis.turnToPoint(10.823, -11.089, 500,{.forwards = false});
    chassis.moveToPoint(10.823, -11.089 ,500,{.forwards = false});

    chassis.setPose(13.5,-13.5,chassis.getPose().theta);
    //end center upper goal push

    //long goal push start
    chassis.moveToPoint(38.53, -46.87, 1000,{.maxSpeed=87},false);

    chassis.turnToPoint(55.04, -52.8,300,{},false);

    load();
    chassis.moveToPoint(55.04, -52.8, 1800,{.maxSpeed=37},false);
    pros::Task::delay(1500);

    chassis.turnToPoint(27, -52.8+2, 300,{.forwards=false},false);
    chassis.moveToPoint(27, -52.8+2, 900,{.forwards=false,.maxSpeed=87},true);
    chassis.waitUntil(10);
    stop_load();
    chassis.waitUntilDone();
    intake();
    pros::Task::delay(1500);
    stop_load();
    scraper_piston.set_value(false);
    //end long goal push
    
    //start hook push
    chassis.moveToPoint(chassis.getPose().x+5, chassis.getPose().y, 300,{},false);

    chassis.turnToPoint(chassis.getPose().x-5,chassis.getPose().y-10.8, 2500,{.forwards=false},false);
    hook_piston.set_value(true);
    pros::delay(100);
    hook_piston.set_value(false);
    chassis.moveToPoint(chassis.getPose().x-5,chassis.getPose().y-10.8, 1000,{.forwards=false,.maxSpeed=87},false);

    chassis.turnToHeading(270+180, 500,{},false);
    chassis.moveToPoint(chassis.getPose().x-20, chassis.getPose().y+5, 1000,{.forwards=false,.maxSpeed=87},false);
    //end hook push
}


void accuracy_tuning()
{
    chassis.setPose(0,0,0);
}

void left_3_3_auton()
{
    //initialize
    hook_piston.set_value(false);
    scraper_piston.set_value(false);
    middle.set_value(false);
    chassis.setPose(47,-14.75,270);
    //initialize

    //center upper goal push start
    chassis.moveToPoint(33.547, -14.75, 9999,{},false);
    load();
    chassis.turnToHeading(230, 300,{},false);
    chassis.moveToPoint(19,-24, 1100,{.maxSpeed=37},true);//reduce timeout, increase maxspeed slowly with testing
    chassis.waitUntil(10);
    scraper_piston.set_value(true);
    chassis.waitUntilDone();
    
    chassis.turnToPoint(5.5+3.9, -11.5-.5, 500,{.forwards=false},false);//-4.5,9.9
    stop_load();
    pros::Task::delay(500);
    middle.set_value(false);
    chassis.moveToPoint(5.5+3.7-.25, -11.5-.25, 1000,{.forwards=false},false);//-4.5,9.9
    pros::delay(350);
    middle_score();
    pros::delay(850);
    stop_load(); 
    chassis.setPose(13.5,-13.5,chassis.getPose().theta);
    //end center upper goal push

    //long goal push start
    chassis.moveToPoint(38.53, -46.5+1, 1000,{.maxSpeed=87},false);

    chassis.turnToPoint(58.54, -53-.5+1,300,{},false);

    load();
    chassis.moveToPoint(58.54, -53-.5+1, 1800,{.maxSpeed=37},false);
    pros::Task::delay(750);

    chassis.turnToPoint(27, -52+.5+1+.5, 300,{.forwards=false},false);
    chassis.moveToPoint(27.5, -52+.5+1+.5, 900,{.forwards=false,.maxSpeed=87},true);
    chassis.waitUntil(10);
    stop_load();
    chassis.waitUntilDone();
    intake();
    pros::Task::delay(1700);
    stop_load();
    scraper_piston.set_value(false);
    //end long goal push
    
    //start hook push
    chassis.moveToPoint(chassis.getPose().x+8, chassis.getPose().y, 300,{},false);

    chassis.turnToPoint(chassis.getPose().x-5,chassis.getPose().y-8.5, 2500,{.forwards=false},false);
    hook_piston.set_value(true);
    pros::delay(100);
    hook_piston.set_value(false);
    chassis.moveToPoint(chassis.getPose().x-5,chassis.getPose().y-8.5, 1000,{.forwards=false,.maxSpeed=87},false);

    chassis.turnToHeading(270+180, 500,{},false);
    chassis.moveToPoint(chassis.getPose().x-20, chassis.getPose().y-3, 1000,{.forwards=false,.maxSpeed=87},false);
    //end hook push

}

void right_3_3_auton()
{
    //initialize
    hook_piston.set_value(false);
    scraper_piston.set_value(false);
    middle.set_value(true);
    chassis.setPose(47,13.75,270);
    //initialize

    //center lower goal push start
    chassis.moveToPoint(33.547, 14.75, 9999,{},false); // initial forward movement
    load();
    chassis.turnToHeading(310, 300,{},false); //turning towards center 3
    chassis.moveToPoint(21.772,22.543, 1100,{.maxSpeed=37},true); //driving at center 3
    chassis.waitUntil(12);
    scraper_piston.set_value(true);
    chassis.waitUntilDone();
     
    chassis.turnToPoint(6.8, 11.5, 500,{},false); //center goal
    pros::Task::delay(500);

    //pros::Task::delay(1500);
    scraper_piston.set_value(false);
    chassis.moveToPoint(13.6, 17.5, 1000,{},true); //center goal
    chassis.waitUntil(7);
    stop_load();
    chassis.waitUntilDone();
    pros::delay(350);
    low_score();
    pros::delay(1000);
    stop_load();
    //end center lower goal push

    //long goal push start
    chassis.moveToPoint(37.03, 45.37-3, 1000,{.forwards = false,.maxSpeed=87},false);
    chassis.turnToPoint(55.04, 44.5-3,300,{},false);

    load();
    scraper_piston.set_value(true);
    chassis.moveToPoint(57.08, 44.5-3, 1800,{.maxSpeed=37},false);
    pros::Task::delay(1000);

    chassis.turnToPoint(22, 48.5-3, 300,{.forwards=false},false);
    chassis.moveToPoint(21, 48.5-3, 900,{.forwards=false,.maxSpeed=87},true);
    chassis.waitUntil(13);
    chassis.waitUntilDone();
    intake();
    pros::Task::delay(1500);
    hook_piston.set_value(true);
    pros::delay(100);
    hook_piston.set_value(false);
    stop_load();
    scraper_piston.set_value(false);
    //stop tuning here___________________________________________//

    //end long goal push
    
    //start hook push stop tuning here
    chassis.moveToPoint(chassis.getPose().x+8, chassis.getPose().y, 300,{},false);

    chassis.turnToPoint(chassis.getPose().x-8,chassis.getPose().y-10.8, 2500,{.forwards=false},false);
    chassis.moveToPoint(chassis.getPose().x-5,chassis.getPose().y-10.8, 1000,{.forwards=false,.maxSpeed=87},false);

    chassis.turnToHeading(270+180, 500,{},false);
    chassis.moveToPoint(chassis.getPose().x-20, chassis.getPose().y+5, 1000,{.forwards=false,.maxSpeed=87},false);
    //end hook push
}

void sawp ()
{
    //initialize
    hook_piston.set_value(false);
    scraper_piston.set_value(false);
    middle.set_value(true);
    chassis.setPose(47,13.75,270);
    //initialize

    //center lower goal push start
    chassis.moveToPoint(33.547, 14.75, 9999,{},false); // initial forward movement
    load();
    chassis.turnToHeading(310, 300,{},false); //turning towards center 3
    chassis.moveToPoint(21.772,22.543, 1100,{.maxSpeed=37},true); //driving at center 3
    chassis.waitUntil(12);
    scraper_piston.set_value(true);
    chassis.waitUntilDone();
     
    chassis.turnToPoint(6.8, 11.5, 500,{},false); //center goal
    pros::Task::delay(500);

    //pros::Task::delay(1500);
    scraper_piston.set_value(false);
    chassis.moveToPoint(13.6, 17.5, 1000,{},true); //center goal
    chassis.waitUntil(7);
    stop_load();
    chassis.waitUntilDone();
    pros::delay(350);
    low_score();
    pros::delay(800);
    stop_load();
    //end center lower goal push

    //long goal push start
    chassis.moveToPoint(37.03, 45.37-3, 1000,{.forwards = false,.maxSpeed=87},false);
    chassis.turnToPoint(55.04, 44.5-3,300,{},false);

    load();
    scraper_piston.set_value(true);
    chassis.moveToPoint(57.08, 44.5-2, 1500,{.maxSpeed=37},false);
    pros::Task::delay(1000);

    chassis.turnToPoint(22, 48.5-3, 300,{.forwards=false},false);
    chassis.moveToPoint(21, 48.5-3, 900,{.forwards=false,.maxSpeed=87},true);
    chassis.waitUntil(13);
    chassis.waitUntilDone();
    intake();
    pros::Task::delay(1200);
    stop_load();
    scraper_piston.set_value(false);
    //stop tuning here___________________________________________//

    //end long goal push

    chassis.setPose(32.701,46.845,90);

    chassis.moveToPoint(39.217, 46.845, 400,{},false); //moves back to not crash into long goal
    pros::delay(250);

    //end long goal

    load();
    //chassis.turnToHeading(177, 300,{},false);
    chassis.turnToPoint(38.174+4.6, 37.1, 300,{},false);
    chassis.swingToPoint(34.5-5, 31.8-5, DriveSide::RIGHT, 1000,{},false);
    chassis.moveToPoint(chassis.getPose().x-11, chassis.getPose().y-13, 1000,{},false);
    chassis.turnToHeading(180, 500,{},false);
    chassis.moveToPoint(chassis.getPose().x+3, chassis.getPose().y-42, 1000,{},false);

    scraper_piston.set_value(true);
    

    chassis.turnToHeading(180-45, 500,{},false);
    chassis.moveToPoint(chassis.getPose().x-10, chassis.getPose().y+7, 1000,{.forwards=false},false);
    stop_load();
    middle.set_value(false);
    intake();
    pros::Task::delay(1000);
    stop_load();

}
void pid_test_linear()
{
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0, 3, 99999,{},false);
    chassis.moveToPoint(0, 12, 99999,{},false);
    chassis.moveToPoint(0, 24, 99999,{},false);
    pros::delay(500);
    //chassis.moveToPoint(0, 0, 99999,{.forwards=false},false);
}

void pid_test_angular()
{
    chassis.setPose(0,0,0);
    chassis.turnToHeading(45,999,{},false);
    chassis.turnToHeading(90,999,{},false);
    chassis.turnToHeading(135,999,{},false);
    chassis.turnToHeading(180,999,{},false);
    chassis.turnToHeading(360,999,{},false);
    chassis.turnToHeading(225,999,{},false);
}