#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../include/main.h"
#include "pros/motors.h"

struct vector {
    double x = 0, y = 0;
    double dist = 0, heading = 0, desiredHeading = 0;
};

extern void move(const int leftVolt, const int rightVolt);
extern void move_straight(const double desiredDist, vector *pCenter, decltype(MOTOR_BRAKE_BRAKE) stopType = MOTOR_BRAKE_BRAKE);
extern void move_straight(const double desiredDist, const int volt, vector *pCenter, decltype(MOTOR_BRAKE_BRAKE) stopType = MOTOR_BRAKE_BRAKE);
extern void move_straight(const float time, const int volt);
extern void move_straight(const int volt, vector *pCenter);

extern void turn(const int baseLeftVolt, const int baseRightVolt, double desiredAngle, vector *pCentre, bool correct = true);

#endif