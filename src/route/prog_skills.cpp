// #include "../include/main.h"
// #include "../globals/globals.hpp"
// #include "../lib/movement.hpp"
// #include "../lib/helper_functions.hpp"
// #include "../lib/scoring.hpp"
// #include "pros/vision.h"

// using namespace pros;

 void prog_skills() {
//     // initial setup
//     vector center = {};

//     unsigned timeElapsed = 0;
//     unsigned desiredSpeed = 2770;
//     pros::Task track_time(stopwatch, &timeElapsed);
//     pros::Task regulate_shooting_speed(regulateFlywheel, &desiredSpeed);
//     setup_robot();

//     pros::Task track_position(odometry, &center);
    
//     // shoot preloads and turn roller
//     move_straight(51, &center); turn_roller(70); delay(600); turn_roller(70);
//     move_straight(-3.4, &center);
//     turn(-25, 25, 359, &center);
//     delay(30);
//         while (desiredSpeed != INT16_MAX) {
//         delay(15);
//     }
//     desiredSpeed = 2760;
//     pros::delay(650);
//     shoot(1000);
//     //pick up next 3 discs and shoot them
//     desiredSpeed = 2000; 
//     intake = 127;
//     turn(-25, 25, 239, &center);
//     move_straight(47,54, &center, MOTOR_BRAKE_COAST);
//     pros::delay(180);
    
//     turn(-21,21, 127.3, &center);
//     shoot(1050);
//     desiredSpeed = 2600; 
//     intake = 127;
//     turn(23,-23, 222,&center);
//     pros::delay(40);
    
//     // pick up stack of 3 discs and shoot them (maybe)
 
//     move_straight(74, 64.0, &center);
//     turn(35,-35, 261, &center);
//     pros::delay(80);
//     move_straight(60, &center); turn_roller(70); pros::delay(600); turn_roller(70);

//     move_straight(-12, -70, &center);
//     turn(35,-35, 265, &center);
//     shoot(1050);
//     intake = 127;
//     turn(-17,17, 182, &center);
//     move_straight(51, &center); turn_roller(70); delay(600); turn_roller(70);
//     move_straight(-3.4, &center);
    
//     //pick up next 3 discs and shoot them
//     desiredSpeed = 2200; 
//     intake = 127;
//     turn(-25, 25, 65, &center);
//     move_straight(47,58, &center, MOTOR_BRAKE_COAST);
//     pros::delay(180);
    
//     turn(-21,21, 324, &center);
//     shoot(1050);
//     intake = 127;
//     turn(23,-23, 40,&center);
//     pros::delay(40);
    
//     // pick up stack of 3 discs and shoot them (maybe)
 
//     move_straight(65, 64.0, &center);
//     turn(35,-35, 87, &center);
//     pros::delay(80);
//     move_straight(60, &center); turn_roller(70); pros::delay(600); turn_roller(70);

//     turn(-20,20, 45, &center);

//     expander1_piston.set_value(1);
//     expander2_piston.set_value(1);




//     track_time.remove();
//     regulate_shooting_speed.remove();
//     track_position.remove();
//     master.print(0, 0, "%d", timeElapsed);
 }