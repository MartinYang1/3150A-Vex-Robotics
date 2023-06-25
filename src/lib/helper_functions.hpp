#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "movement.hpp"

extern const double wheelDiam;    // the diameter of the wheels of the drive train
extern const double motorToWheelRatio;    // the gear ratio of the motor to the drive train wheel
extern const double robotWidth;

extern double get_dist_travelled();
extern double get_heading();
extern double get_move_speed();
extern double get_move_voltage();

extern double PID(double input, double target, double Kp, double Ki, double Kd, int &prevError, int &integral, int direction = 1);
extern void odometry2(void *param);
extern void stopwatch(void *param);
void setup_robot();

#endif