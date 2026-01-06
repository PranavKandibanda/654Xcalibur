#include "lemlib/asset.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/rtos.hpp"
#include <future>
#include "autons.h"
//ASSET(testSum_txt);
ASSET(PushCenter3ToGoal_33_txt);
ASSET(PushCenter3ToGoal_end_33_txt);

void skills()
{
    scraper_piston.set_value(false);
    middle.set_value(true);
    chassis.setPose(-47.387,-14.279,180);

    scraper_piston.set_value(true);
    chassis.turnToPoint(-47.387, -46.93, 500,{},false);
    chassis.moveToPoint(-47.387, -46.93, 500,{},false);

    chassis.turnToPoint(-57.561, -46.972, 200,{},false);
    chassis.moveToPoint(-58.019, -46.972, 200,{},false);
    

    load();
    pros::delay(500);
    stop_load();

    chassis.moveToPoint(-39.779, -47.008, 100, {.forwards = false}, false);

    chassis.turnToPoint(-39.679, -56.807, 100, {.forwards = false}, false);
    chassis.moveToPoint(-39.679, -56.807, 100, {.forwards = false}, false);

    chassis.turnToPoint(39.796, -56.541, 500,{.forwards = false},false);
    chassis.moveToPoint(39.796, -56.541, 500,{.forwards = false},false);

    chassis.swingToPoint(30.578, -47.008, lemlib::DriveSide::LEFT, 100,{.forwards = false},false);
}

void blue_5_3_auton_left() //unifinished, moving onto 3+3 push
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
}


void accuracy_tuning()
{
    chassis.setPose(0,0,0);
}

void blue_3_3_auton_left()
{
    hook_piston.set_value(false);
    scraper_piston.set_value(false);
    middle.set_value(false);
    chassis.setPose(47,-14.75,270);
    chassis.moveToPoint(33.547, -14.75, 9999,{},false);
    load();
    chassis.turnToHeading(230, 300,{},false);
    chassis.moveToPoint(19,-24, 1100,{.maxSpeed=37},false);//reduce timeout, increase maxspeed slowly with testing
    
    chassis.turnToPoint(4.5, -9.9, 500,{.forwards=false},false);
    stop_load();
    pros::Task::delay(500);
    middle.set_value(false);
    chassis.moveToPoint(4.5, -9.9, 1000,{.forwards=false},false);
    pros::delay(350);
    intake();
    pros::delay(2000);
    stop_load(); 
    chassis.setPose(13.5,-13.5,chassis.getPose().theta);

    chassis.moveToPoint(38.53, -46.87, 1000,{},false);

    chassis.turnToPoint(56.04, -54.2,300,{},false);
    scraper_piston.set_value(true);

    load();
    chassis.moveToPoint(56.04, -54.2, 1800,{.maxSpeed=37},false);
    pros::Task::delay(1500);
    stop_load();

    chassis.turnToPoint(6.3, -54.2, 300,{.forwards=false},false);
    chassis.moveToPoint(6.3, -54.2, 900,{.forwards=false,.maxSpeed=87},false);
    middle_score();
    pros::delay(850);
    stop_load();
    

}

void sawp ()
{
    //initialize
    hook_piston.set_value(false);
    scraper_piston.set_value(false);
    middle.set_value(true);
    chassis.setPose(47,14.75,270);
    //initialize

    //center lower goal push start
    chassis.moveToPoint(33.547, 14.75, 9999,{},false);
    load();
    chassis.turnToHeading(310, 300,{},false);
    chassis.moveToPoint(19,24, 1100,{.maxSpeed=37},true);
    chassis.waitUntil(12);
    scraper_piston.set_value(true);
    chassis.waitUntilDone();
    scraper_piston.set_value(false);

    chassis.turnToPoint(4.5, 9.9, 500,{},false);
    pros::Task::delay(500);

    //pros::Task::delay(1500);

    chassis.moveToPoint(8.5, 16.3, 1000,{},true);
    chassis.waitUntil(7);
    stop_load();
    chassis.waitUntilDone();
    pros::delay(350);
    low_score();
    pros::delay(800);
    stop_load();
    //end center lower goal push

    load();
    chassis.moveToPoint(23.8, 27.8, 1000,{.forwards=false},false);
    //chassis.setPose(24,24,chassis.getPose().theta);


    //upper goal push start
    
    chassis.moveToPoint(23.8,-10, 1100,{},true);
    chassis.waitUntil(35);
    scraper_piston.set_value(true);
    chassis.waitUntilDone();
    scraper_piston.set_value(false);
    
    //y value was -24
    chassis.moveToPoint(19,-28, 1100,{.maxSpeed=7},false);//reduce timeout, increase maxspeed slowly with testing
    chassis.turnToPoint(4.5, -9.9, 500,{.forwards=false},false);
    stop_load();
    pros::Task::delay(500);
    middle.set_value(false);
    chassis.moveToPoint(5, -9.9, 1000,{.forwards=false},false);
    pros::delay(350);
    middle_score();
    pros::delay(1000);
    stop_load();
    //upper goal push end

    //loader and long goal push start
    chassis.setPose(13.5,-13.5,chassis.getPose().theta);

    chassis.moveToPoint(38.53, -46.87, 1000,{},false);

    chassis.turnToPoint(56.04, -55.5,800,{},false);
    scraper_piston.set_value(true);

    load();
    chassis.moveToPoint(56.04, -55.5, 1800,{.maxSpeed=37},false);
    pros::Task::delay(1500);
    stop_load();

    chassis.turnToPoint(24, -54.4, 300,{.forwards=false},false);
    chassis.moveToPoint(24, -54.4, 900,{.forwards=false,.maxSpeed=87},false);
    intake();
    pros::delay(850);
    stop_load();
    //loader and long goal push end

}
void pid_test_linear()
{
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0, 3, 99999);
    chassis.moveToPoint(0, 12, 99999);
    chassis.moveToPoint(0, 24, 99999);
    chassis.moveToPoint(0, -24, 99999);
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