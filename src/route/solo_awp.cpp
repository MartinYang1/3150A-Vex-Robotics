#include "../include/main.h"
#include "../globals/globals.hpp"
#include "../lib/movement.hpp"
#include "../lib/helper_functions.hpp"
#include "../lib/scoring.hpp"
#include "pros/vision.h"

using namespace pros;

void solo_awp() {
    // initial setup
    vector center = {};

    unsigned timeElapsed = 0;
    unsigned desiredSpeed = 3230;
    pros::Task regulate_shooting_speed(regulateFlywheel, &desiredSpeed);
    
    // shoot preloads and turn roller
    move_straight(60, &center); turn_roller(100);
    move_straight(-2.4, &center);
    //pick up next 3 discs and shoot them
    desiredSpeed = 3280; 
    intake = 127;
    turn(-26, 26, 234.5, &center);
    move_straight(47.5,55, &center, MOTOR_BRAKE_COAST);
    pros::delay(180);
    
    turn(25,-25, 314.4, &center);
    shoot(950);
    intake = 127;
    turn(-24,24, 225.5,&center);
    pros::delay(20);
    
    // pick up stack of 3 discs and shoot them (maybe)
 
    move_straight(59.5, 64.0, &center);
    turn(25,-25, 277, &center);
    shoot(1100);
    intake = 127;
    turn(-25,25, 221, &center);
    pros::delay(40);
    move_straight(4.5, 65.0, &center);
    turn(26,-26, 271, &center);
    move_straight(60, &center); turn_roller(100);



    regulate_shooting_speed.remove();

    master.print(0, 0, "%d", timeElapsed);
}