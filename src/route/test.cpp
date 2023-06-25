#include "../include/main.h"
#include "../globals/globals.hpp"
#include "../lib/movement.hpp"
#include "../lib/helper_functions.hpp"
#include "../lib/scoring.hpp"
#include "pros/vision.h"

using namespace pros;

 void test() {
//     // initial setup
     vector center = {};
          pros::Task track_position(odometry2, &center);

     //move(50, 50);
     turn(-40, 40, 270, &center, false);
     std::cout << "Hi";
     turn(20, -20, 270, &center);
     track_position.remove();


 }
