#include "../include/main.h"
#include "../globals/globals.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"
#include "pros/motors.h"

#include <cmath>
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

/** Turns the robot to an absolute angle
 * 
 * @param baseLeftVolt the base voltage for the left motors in volts, from -127 to 127
 * @param baseRightVolt the voltage for the right motors in volts, from -127 to 127
 * @param desiredAngle in degrees in the interval (0, 360]
 * @param pCenter the pointer to the vector data structure for the robot
 */
void turn(const int baseLeftVolt, const int baseRightVolt, double desiredAngle, vector *pCentre, bool correct) {
    int prevErrorHeading = 0, integralHeading = 0;
    pCentre->desiredHeading = desiredAngle;
    double currAngle = imu_sensor.get_heading();
    
    if (baseLeftVolt > baseRightVolt) {
        if (currAngle < desiredAngle) {
            while (currAngle < desiredAngle) { 
                currAngle = imu_sensor.get_heading();         
                move(baseLeftVolt + PID(currAngle, desiredAngle, 0.6, 0, 0, prevErrorHeading, integralHeading), 
                        baseRightVolt - PID(currAngle, desiredAngle, 0.6, 0, 0, prevErrorHeading, integralHeading));
                
                pros::delay(15);
            }
        }
        else if (currAngle > desiredAngle) {
            desiredAngle = desiredAngle + (360 - currAngle);
            currAngle = 0; double prevAngle = imu_sensor.get_heading();
            
            while (currAngle + 2 < desiredAngle) {
                if (imu_sensor.get_heading() - prevAngle < -2) 
                    prevAngle = imu_sensor.get_heading();
                currAngle += imu_sensor.get_heading() - prevAngle;
                
                move(baseLeftVolt + PID(currAngle, desiredAngle, 0.6, 0, 0, prevErrorHeading, integralHeading), 
                        baseRightVolt - PID(currAngle, desiredAngle, 0.6, 0, 0, prevErrorHeading, integralHeading));
                
                prevAngle = imu_sensor.get_heading();  
                pros::delay(15);
            }
        }
    }
    else {
        if (0 <= currAngle && desiredAngle > currAngle) {
            desiredAngle = -(currAngle + (360 - desiredAngle));
            currAngle = 0; double prevAngle = imu_sensor.get_heading();
            
            while (currAngle - 2 > desiredAngle) {
                if (imu_sensor.get_heading() - prevAngle > 2) 
                    prevAngle = imu_sensor.get_heading();
                currAngle += imu_sensor.get_heading() - prevAngle;
                
                move(baseLeftVolt + PID(currAngle, desiredAngle, 0.5, 0, 0, prevErrorHeading, integralHeading), 
                        baseRightVolt - PID(currAngle, desiredAngle, 0.5, 0, 0, prevErrorHeading, integralHeading));
                
                prevAngle = imu_sensor.get_heading();
                pros::delay(15);
            }
        }
        else if (currAngle < 360 && currAngle > desiredAngle) {
            desiredAngle = desiredAngle - 360;
            currAngle -= 360;  
            
            while (currAngle > desiredAngle) {
                currAngle = imu_sensor.get_heading() - 360;
                move(baseLeftVolt + PID(currAngle, desiredAngle, 0.5, 0, 0, prevErrorHeading, integralHeading), 
                        baseRightVolt - PID(currAngle, desiredAngle, 0.5, 0, 0, prevErrorHeading, integralHeading));
                
                pros::delay(15);
            }
        }
    }
    if (correct) {
        std::cout << imu_sensor.get_heading() << std::endl;
        turn(-baseLeftVolt*0.5, -baseRightVolt*0.5, desiredAngle, pCentre, false);
    }
    move(MOTOR_BRAKE_BRAKE, MOTOR_BRAKE_BRAKE);
    pros::delay(100);
    pCentre->heading = imu_sensor.get_heading(); 
}

/**
 * @param desiredDist the distance to travel, in inches
 * @param pCenter the pointer to the vector data structure for the robot
 * @param stopType the type of brake mechanism the robot uses
 */
void move_straight(const double desiredDist, const double desiredVolt, vector *pCenter, decltype(MOTOR_BRAKE_BRAKE) stopType) {
    double prevLeftPos = leftMidMotor.get_position(), prevRightPos = rightMidMotor.get_position();   // the previous motor encoder value of each side of the drive train
    double currDist = 0;
    
    int prevErrorDist = 0, integralDist = 0;
    int prevErrorHeading = 0, integralHeading = 0;

    double startingVolt = get_move_voltage();
    double currVolt = startingVolt;
    while (abs(currDist) < abs(desiredDist)) {
        if (abs(currDist) < abs(desiredDist) / 4)
            currVolt += (desiredVolt - startingVolt) / (abs(desiredDist) / 4);
        else if (abs(currDist) < abs(desiredDist) * 3/4)
            currVolt = currVolt;
        else
            currVolt -= (desiredVolt - startingVolt) / (abs(desiredDist) / 4)
        
        if (pCenter->desiredHeading > 180)
            move(volt + PID(get_heading(), pCenter->desiredHeading-360, 1.5, 0.01, 2, prevErrorHeading, integralHeading), 
                volt - PID(get_heading(), pCenter->desiredHeading-360, 1.5, 0.01, 2, prevErrorHeading, integralHeading));
        else
            move(volt + PID(get_heading(), pCenter->desiredHeading, 1.5, 0.01, 2, prevErrorHeading, integralHeading), 
                volt - PID(get_heading(), pCenter->desiredHeading, 1.5, 0.01, 2, prevErrorHeading, integralHeading));

        currDist += (leftMidMotor.get_position()-prevLeftPos + rightMidMotor.get_position()-prevRightPos)/2 
                    * motorToWheelRatio/360*(M_PI*wheelDiam);
        
        prevLeftPos = leftMidMotor.get_position(), prevRightPos = rightMidMotor.get_position();
        pros::delay(15);
    }
    if (stopType == MOTOR_BRAKE_BRAKE)
        move(stopType, stopType);
    pros::delay(200);
    pCenter->heading = imu_sensor.get_heading();
}

// move at a constant speed
void move_straight(const double desiredDist, const int volt, vector *pCenter, decltype(MOTOR_BRAKE_BRAKE) stopType) {
    double prevLeftPos = leftMidMotor.get_position(), prevRightPos = rightMidMotor.get_position();   // the previous motor encoder value of each side of the drive train
    double currDist = 0;

    int prevErrorDist = 0, integralDist = 0;
    int prevErrorHeading = 0, integralHeading = 0;
    while (abs(currDist) < abs(desiredDist)) {
        if (pCenter->desiredHeading > 180)
            move(volt + PID(get_heading(), pCenter->desiredHeading-360, 0.9, 0.01, 1, prevErrorHeading, integralHeading), 
                volt - PID(get_heading(), pCenter->desiredHeading-360, 0.9, 0.01, 1, prevErrorHeading, integralHeading));
        else
            move(volt + PID(get_heading(), pCenter->desiredHeading, 0.9, 0.01, 1, prevErrorHeading, integralHeading), 
                volt - PID(get_heading(), pCenter->desiredHeading, 0.9, 0.01, 1, prevErrorHeading, integralHeading));
        
        currDist += (leftMidMotor.get_position()-prevLeftPos + rightMidMotor.get_position()-prevRightPos)/2 
                    * motorToWheelRatio/360*(M_PI*wheelDiam);
        
        prevLeftPos = leftMidMotor.get_position(), prevRightPos = rightMidMotor.get_position();
        pros::delay(15);
    }
    if (stopType == MOTOR_BRAKE_BRAKE)
        move(stopType, stopType);
    pros::delay(200);
    pCenter->heading = imu_sensor.get_heading();
}

/** Moves the robot a given amount of time forwards or backwards
 * 
 * @param time the time to travel for, in seconds
 * @param volt the voltage for the drive train motors
*/
void move_straight(const float time, const int volt) {
    static unsigned timeElapsed = 0;    // in milliseconds
    pros::Task track_time(stopwatch, &timeElapsed);
    while (timeElapsed < time * 1000) {
        move(volt, volt);
        pros::delay(1);
    }
    track_time.remove();
    move(MOTOR_BRAKE_HOLD, MOTOR_BRAKE_HOLD);
}
