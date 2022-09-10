#include "../include/main.h"
#include "../globals/globals.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"

#include <math.h>
#include <vector>

/** Moves the robot continuously based on voltage. A negative
 * value moves the robot backwards, while a positive
 * value moves the robot forwards.
 * 
 * @param leftVolt the voltage of the motors on the left side
 * of the drive train, from -127 to 127 volts
 * @param rightVolt the voltage of the motors on the right side
 * of the drive train, from -127 to 127 volts
 */
void move(const int leftVolt, const int rightVolt){
    leftFrontMotor = leftVolt; leftMidMotor = leftVolt; leftBackMotor = leftVolt;
    rightFrontMotor = rightVolt; rightMidMotor = rightVolt; rightBackMotor = rightVolt;
}

// //closed loop movement using PID
// void move_closed_loop(double distanceLeft, double distanceRight){
//     double lastErrorLeft = 0.1;
//     double lastErrorRight = 0.1;
//     double startLeft = distance(leftBackMotor);
//     double startRight = distance(rightBackMotor);

//     while (lastErrorLeft + lastErrorRight != 0){
//         PID(distanceLeft, distance(leftBackMotor) - startLeft, &lastErrorLeft);
//         PID(distanceRight, distance(rightBackMotor) - startRight, &lastErrorRight);
//     }
// }

/** Turns the robot to a desired angle,
 * relative to its starting pos when the gyro sensor was calibrated
 * 
 * @param baseLeftVolt the base voltage for the motors on the left side 
 * of the drive train in volts, from -127 to 127
 * @param baseRightVolt the voltage for the motors on the right side 
 * of the drive train in volts, from -127 to 127
 * @param desiredAngle in degrees, to 2 decimal places. A negative angle turns the robot counter-clockwise
 * and a postive angle turns the robot clockwise
 */
void turn(const int baseLeftVolt, const int baseRightVolt, const float desiredAngle) {
    //  if (abs(leftVolt) > 127 || abs(rightVolt) > 127)
    //      throw std::out_of_range;
    
    float currentAngle = get_heading(), targetAngle = currentAngle + desiredAngle;
    int totalCurrAngle = 0;  // needed because get_heading() doesn't return a value higher than 180.
    short headingReversed = 1;
    while (abs(currentAngle) <= abs(targetAngle)) { 
        currentAngle = headingReversed * get_heading() + totalCurrAngle;
        move(baseLeftVolt + PID(currentAngle, targetAngle, 0.6, 0, 0.2), 
                baseRightVolt - PID(currentAngle, targetAngle, 0.6, 0, 0.2));
        
        if (abs(currentAngle) >= 177) {
            headingReversed *= -1;
            totalCurrAngle = currentAngle;
        }
        pros::delay(15);
    }
    move(MOTOR_BRAKE_BRAKE, MOTOR_BRAKE_BRAKE);
}

/** Moves the robot a given distance forwards or backwards
 * 
 * @param desiredDist the distance to travel, in inches
 * @param stopType the type of brake mechanism the robot uses
 */
void move_straight(const double desiredDist, decltype(MOTOR_BRAKE_BRAKE) stopType) {
    leftBackMotor.tare_position(); rightBackMotor.tare_position();
    leftMidMotor.tare_position(); rightMidMotor.tare_position();
    leftFrontMotor.tare_position(); rightFrontMotor.tare_position();
    
    double currDist = 0; const unsigned baseVolt = 20;
    while (currDist < desiredDist) {
        const double volt = (desiredDist < 0) ? PID(currDist, desiredDist, 1, 0.1, 0.5) - baseVolt
                                            : PID(currDist, desiredDist, 1, 0.1, 0.5) + baseVolt;
        move(volt + PID(get_heading(), 0, 1, 0.02, 0.5), 
                volt - PID(get_heading(), 0, 1, 0.02, 0.5));
        currDist = get_dist_travelled();
        pros::delay(15);
    }
    move(stopType, stopType);
}

void move_straight(const unsigned time) {
    
}