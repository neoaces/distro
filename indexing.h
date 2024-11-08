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

// Calling this function means that there are too many cubes inside the robot.
// The conveyor belt will handle the removal of the cube in the robot.
void ind_dispose(state_t &state) {

}
