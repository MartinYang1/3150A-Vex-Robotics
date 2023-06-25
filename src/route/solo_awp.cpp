// #include "../include/main.h"
// #include "../globals/globals.hpp"
// #include "../lib/movement.hpp"
// #include "../lib/helper_functions.hpp"
// #include "../lib/scoring.hpp"
// #include "pros/vision.h"

// using namespace pros;

 void solo_awp() {
//     // initial setup
//     vector center = {};

//     unsigned timeElapsed = 0;
//     unsigned desiredSpeed = 2770;
//     pros::Task track_time(stopwatch, &timeElapsed);
//     pros::Task regulate_shooting_speed(regulateFlywheel, &desiredSpeed);
//     setup_robot();

//     pros::Task track_position(odometry, &center);
    
//     // shoot preloads and turn roller
//     move_straight(51, &center); turn_roller(100); delay(400);
//     move_straight(-3.4, &center);
//     turn(-25, 25, 355, &center);
//     delay(30);
//     pros::delay(2500);
//     while (desiredSpeed != INT16_MAX) {
//         delay(15);
//     }
//     desiredSpeed = 2520;
//     pros::delay(250);
//     shoot(1000);
//     //pick up next 3 discs and shoot them
//     desiredSpeed = 2400; 
//     intake = 127;
//     turn(-25, 25, 239, &center);
//     move_straight(51,58, &center, MOTOR_BRAKE_COAST);
//     pros::delay(180);
    
//     turn(23,-23, 313, &center);
//     shoot(1050);
//     intake = 127;
//     turn(-23,23, 224,&center);
//     pros::delay(40);
    
//     // pick up stack of 3 discs and shoot them (maybe)
 
//     move_straight(68.0, 64.0, &center);
//     turn(35,-35, 261, &center);
//     pros::delay(80);
//     move_straight(60, &center); turn_roller(100);


//     track_time.remove();
//     regulate_shooting_speed.remove();
//     track_position.remove();
//     master.print(0, 0, "%d", timeElapsed);
 }