// #include "../include/main.h"
// #include "../globals/globals.hpp"
// #include "../lib/movement.hpp"
// #include "../lib/helper_functions.hpp"
// #include "../lib/scoring.hpp"
// #include "pros/vision.h"

//  using namespace pros;

  void far_auto() {
//     // initial setup
//     vector center = {};
//     unsigned timeElapsed = 0;
//     unsigned desiredSpeed = 2770;

//     pros::Task setupFlywheelSpeed(setupFlywheel, &desiredSpeed);
//     pros::Task track_time(stopwatch, &timeElapsed);

//     setup_robot();

//     pros::Task track_position(odometry, &center);

//     // turn roller
//     move_straight(22.0, &center);
//     turn(35, 0, 89, &center);
//     move_straight(0.6, 51);
//     //move_straight(51, &center); 
//     turn_roller(100); delay(100);
    
//     // shoot preloads
//     move_straight(-4.0, &center);
//     turn(29, -29, 93, &center);
//     while (desiredSpeed != INT16_MAX) {
//         delay(15);
//     }
//     desiredSpeed = 2770; setupFlywheelSpeed.remove();
//     delay(850);
//     shoot(2770, 2);
//     move_straight(5.0, 60.0,&center);
//     desiredSpeed = 2600;
//     Task changeFlywheelSpeed(regulateFlywheel, &desiredSpeed);

//     // pick up row of 3 discs
//     intake = 127;
//     turn(29,-29,220,&center);
//     move_straight(69.3, 59.0, &center);
//     turn(-29,29,150,&center);
//     delay(50);
//     changeFlywheelSpeed.suspend();
//     shoot(2600, 3);
//     // desiredSpeed = 2600;
//     // move_straight(1, 61.0, &center);
//     // turn(-29,29,90,&center);
//     // //pickup discs next to the goal
//     // intake=127;
//     // move_straight(43.0, 80.0, &center);
//     // move_straight(-40.0,-61.0,&center);
//     // turn(29,-29,135.0,&center);
//     // move_straight(-5.0,-61.0,&center);
//     // shoot(800);

//     // cleanup program
//     track_time.remove();
//     track_position.remove();
//     master.print(0, 0, "%d", timeElapsed);
   }