#pragma once
#include "types.h"

void motorControl(int encoderCount, int direction, int motorLabel) {
      while (abs(nMotorEncoder[motorLabel]) <= encoderCount)
                  {
                        motor[motorLabel]= direction*10;
                  }
                  motor[motorLabel]=0;
                  nMotorEncoder[motorLabel] = 0;
}


/*
void ind_index(state_t &state)
{
      nMotorEncoder[motorB] = 0;
      nMotorEncoder[motorC] = 0;

      if (getColorName(S2) == colorRed)
      {
      		// Check to be made: if the color bay is full i.e peek_stack -> -1, then call ind_dispose, which will throw away the block
            //turns sorter to left direction
            motorControl(10,1,motorB);

            //powers conveyor belt to move the item to sorter
            motorControl(20,1,motorC);

            //makes conveyor go in opposite direction to reset for next package
            motorControl(20,-1,motorC);

            //resets sorter to center configuration
            motorControl(10,-1,motorB);
      }

      else if (getColorName(S2) == colorBlue)
      {
            //powers conveyor belt to move the item to sorter
            motorControl(20,1,motorC);

            //makes conveyor go in opposite direction to reset for next package
            motorControl(20,-1,motorC);
      }

      else if (getColorName(S2) == colorGreen)
      {
            //turns sorter to right direction
            motorControl(10,1,motorB);

            //powers conveyor belt to move the item to sorter
            motorControl(20,1,motorC);

            //makes conveyor go in opposite direction to reset for next package
            motorControl(20,-1,motorC);

            //resets sorter to center configuration
            motorControl(10,-1,motorB);
      }
}
*/

void loading(state_t &state) {
		for(int i = 0; i < 6; i++) {
			switch (getColorName(S4)) {
				case colorRed:
					motor[motorA] = -25;
					wait1Msec(750);
					motor[motorA] = 0;
					break;
				case colorGreen:
					motor[motorA] = 25;
					wait1Msec(750);
					motor[motorA] = 0;
					break;
				case colorYellow:
					//Assuming sorter is to the right
					nMotorEncoder[motorA] = 0;
					setMotorTarget(motorA, 60, 15);
					break;
			}
			nMotorEncoder[motorD] = 0;
			motor[motorC] = motor[motorD] = 25;
			while((abs(nMotorEncoder[motorD])) <= 110) {};
			motor[motorC] = motor[motorD] = 0;
			nMotorEncoder[motorB] = 0;
			setMotorTarget(motorB, 950, 40);
			waitUntilMotorStop(motorB);
		  wait1Msec(1000);
			setMotorTarget(motorB, 0, 40);
			waitUntilMotorStop(motorB);
			motor[motorA] = -25;
			wait1Msec(500);
			motor[motorA] = 0;
			wait1Msec(1000);
		}

		state.mode = Route;
}
