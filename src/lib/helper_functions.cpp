/*
 * Functions that support the usage of other functions,
 * such as PID(), go here
 */

#include "../include/main.h"
#include "../globals/globals.hpp"
#include "helper_functions.hpp"
#include "movement.hpp"
#include "scoring.hpp"

#include <math.h>

const double wheelDiam = 3.25;
const double motorToWheelRatio = 3 / 5.0 / 0.8;
const double robotWidth = 12;

inline void reset_drive_train() {
    leftBackMotor.tare_position(); leftMidMotor.tare_position(); rightBackMotor.tare_position();
    leftFrontMotor.tare_position(); rightMidMotor.tare_position(); rightFrontMotor.tare_position();
}

/** Setups the robot for autonomous by resetting motors and sensors
*/
void setup_robot() {
    imu_sensor.reset();
    pros::delay(2000);
    imu_sensor.tare_heading();
    pros::delay(50);

    reset_drive_train();
    intake.tare_position();

    pros::delay(50);
    intake = 127;
}

/** Gets the distance travelled in a linear path by the robot
 * 
 * @return the distance travelled by the motors, in inches
 */
double get_dist_travelled() {
    double degreesTravelled = (leftBackMotor.get_position() + rightBackMotor.get_position()) / 2;
    return degreesTravelled * motorToWheelRatio / 360 * (M_PI*wheelDiam);
}

/** Gets the heading of the robot from its gyro sensor
 * relative to its initial direction. A clockwise turn
 * is in positive degrees, whereas a counter-clockwise turn
 * is in negative degrees.
 * 
 * @returns the heading of the robot in degrees,
 * in the range (-180, 180]
 */
double get_heading() {
    double heading = imu_sensor.get_heading();
    if (heading > 180)
        heading -= 360;  // sets the heading to a neg val if the robot's heading is counterclockwise
    return heading;
}

/** Gets the speed of the robot's drive train
 * 
 * @return the speed in RPM of the robot's drive train
 */
double get_move_speed() {
    return (leftBackMotor.get_actual_velocity() + rightBackMotor.get_actual_velocity()
            + leftFrontMotor.get_actual_velocity() + rightFrontMotor.get_actual_velocity())/4 * motorToWheelRatio;
}

/** Gets the voltage that the drive train motors are running at
 * 
 * @return the voltage, in volts
 */
double get_move_voltage() {
    return (leftBackMotor.get_voltage() + rightBackMotor.get_voltage()
            + leftFrontMotor.get_voltage() + rightFrontMotor.get_voltage())/4.0 / 1000;
}

/** A general-purpose PID function that provides the correction
 * needed for a given system
 * 
 * @param input the input from the system
 * @param target the value the system is trying to achieve
 * @param Kp the proportional constant
 * @param Ki the integral constant
 * @param Kd the derivative constant
 * @param direction the direction of the correction
 * @return the correction feedback for the system
 */
double PID(double input, double target, double Kp, double Ki, double Kd, int &prevError, int &integral, int direction) {    
    double error = (target - input) * direction;
    double derivative = error - prevError;  // only an approximation
    integral = 0.5 * integral + error;  // only an approximation
    prevError = error;

    return Kp * error + Kd * derivative + Ki * integral;
}

/** A stopwatch with a frequency of 1000Hz
 * 
 * @param param the pointer to the variable storing the time elapsed
*/
void stopwatch(void *param) {
    while (true) {
        *static_cast<unsigned*>(param) += 1;
        pros::delay(1);
    }
}

/** Calculates the position of the robot in the field
 * as (x, y) coordinates
 * 
 * @param param the pointer to the vector data structure for the robot
*/
void odometry2(void* param) {
    vector *pCenter = static_cast<vector*>(param);
    double L, R, deltaX, deltaY, alpha, hypotenuse;
    while (true) {
        L = leftBackMotor.get_position() * motorToWheelRatio / 360 * (M_PI*wheelDiam);
        R = rightBackMotor.get_position() * motorToWheelRatio / 360 * (M_PI*wheelDiam);
        if (L==R) {
            deltaY = L * cos(pCenter->heading) - pCenter->y; deltaX = R * sin(pCenter->heading)-pCenter->x;
            pCenter->x += deltaX; pCenter->y += deltaY;
            master.print(0, 0, "%f", pCenter->y);
        }
        else {
            // the angle turned
            alpha = pCenter-> heading;
            hypotenuse = 2 * (L/alpha + robotWidth/2) * sin(alpha/2);

            deltaY = hypotenuse * cos(pCenter->heading + alpha/2) - pCenter->y;
            deltaX = hypotenuse * sin(pCenter->heading + alpha/2) - pCenter->x;

            pCenter->x += deltaX; pCenter->y += deltaY;
            master.print(0, 0, "%f", pCenter->y);
        }
        pros::delay(10);
    }
}

// void odometry(void* param) {
//     vector *pCenter = static_cast<vector*>(param);
//     double C, deltaX, deltaY, alpha;
//     while (true) {
//         C = centerMotor.get_position() = motorToWheelRatio/360 * (M_PI*wheelDiam);

//         // the angle turned
//         alpha = pCenter-> heading;

//         deltaY = C * sin(pCenter->heading + alpha/2) - pCenter->y;
//         deltaX = C * cos(pCenter->heading + alpha/2) - pCenter->x;

//         pCenter->x += deltaX; pCenter->y += deltaY;
//         std::cout << pCenter->x << "\t" << pCenter->y;

//         pros::delay(10);
//     }
// }
