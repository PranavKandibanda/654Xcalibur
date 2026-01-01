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
#include "autons.h"

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
    /*chassis.moveToPose(18.823, -18.089, 240,600,{.forwards = false},false);
    intake();
    pros::delay(500);*/
    /*chassis.moveToPose(18.809, -38.131, 254.4,500,{},false);
    chassis.moveToPose(36.662, -43.175, 206.4,300,{.lead=3},false);
    chassis.moveToPose(30.226, -47.227, 270, 1000,{.forwards=false},false);
    //TODO RUN INTAKE FOR 3 SECONDS HERE
    scraper_piston.set_value(true);

    chassis.moveToPoint(56.157, -47.098, 2000,{.minSpeed=67},false);
    chassis.moveToPoint(30.226, -47.227, 1000);*/
    //TODO RUN INTAKE FOR 3 SECONDS HERE*/
}

ASSET(testSum_txt);
ASSET(testSum2_txt);

void blue_3_3_auton_left()
{
    hook_piston.set_value(false);
    scraper_piston.set_value(false);
    middle.set_value(false);
    /*chassis.setPose(49.554,-15.874,270);

    chassis.moveToPoint(44.554,-15.874, 50,{},false);

    load();
    chassis.turnToPoint(11.95,-25.037,400);
    chassis.moveToPoint(11.95,-25.037,610,{.maxSpeed = 57});
    
    // @TODO run intake code here
    chassis.waitUntil(19);
    pros::Task::delay(400);
    scraper_piston.set_value(true);
    pros::delay(600);
    chassis.cancelMotion();
    //scraper_piston.set_value(false);

    chassis.moveToPoint(23.05, -23.316, 500,{.forwards = false},false);

    chassis.turnToHeading(140,500,{.direction=lemlib::AngularDirection::CCW_COUNTERCLOCKWISE},false);

    chassis.moveToPoint(15.581, -11.152, 500,{.forwards = false},false);
    intake();
    middle.set_value(false);
    pros::delay(2000);
    stop_load();*/
    chassis.setPose(50.162,-16.804,270);
    chassis.moveToPoint(36.38,-16.804,500,{.maxSpeed=67},false);
    load();
    chassis.follow(testSum2_txt,9.3,5500,true,false);
    scraper_piston.set_value(true);
    pros::delay(300);
    chassis.turnToPoint(11.566, -11.887,400,{.forwards=false},false);
    chassis.moveToPoint(11.566, -11.887, 430,{.forwards = false},false);
    middle.set_value(false);
    pros::delay(200);
    intake();
    pros::Task::delay(2000);
    stop_load();

}

void pid_test_linear()
{
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0, 24, 99999);
}

void pid_test_angular()
{
    chassis.setPose(0,0,0);
    chassis.turnToHeading(0,45,{},500);
    chassis.turnToHeading(0,90,{},500);
    chassis.turnToHeading(0,180,{},500);
    chassis.turnToHeading(0,0,{},500);

}