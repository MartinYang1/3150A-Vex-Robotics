#include "../include/main.h"
#include "globals/globals.hpp"
#include "pros/misc.h"
#include "lib/movement.hpp"
#include "lib/scoring.hpp"
#include "lib/helper_functions.hpp"

void opcontrol() {
         vector center = {};
          pros::Task track_position(odometry2, &center);
    unsigned shootingSpeed = 2000;
    pros::Task changeFlywheelSpeed(regulateFlywheel, &shootingSpeed);

    expander1_piston.set_value(0);
    expander2_piston.set_value(0);

    flywheel_indexer.set_value(0);
    int intake_state=1;
    int flywheel_state=0;
    bool shooterReady = false;
    while (true) {
        int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int turnRate = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        move(power + turnRate, power - turnRate);
        if(master.get_digital(DIGITAL_L1))
        {
            intake=-127;
        }
        else if(master.get_digital(DIGITAL_L2))
        {
            intake=0;
        }
        else 
        {
            intake=127;
        }
        if (master.get_digital(DIGITAL_R2) )
 {
                flywheel_indexer.set_value(1);
                pros::delay(150);
                flywheel_indexer.set_value(0);
 }
        if (master.get_digital(DIGITAL_R1))
 {
            //vector center11 = {};
            //aim_shot(&center11);
        }

        if(master.get_digital(DIGITAL_UP) && master.get_digital (DIGITAL_DOWN) && master.get_digital (DIGITAL_RIGHT) && master.get_digital (DIGITAL_LEFT))
        {
            expander1_piston.set_value(1);
            expander2_piston.set_value(1);
        }
        else
        {
            expander1_piston.set_value(0);
            expander2_piston.set_value(0);
        }

    }
    track_position.remove();
}