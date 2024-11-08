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


void ind_index(state_t &state, color_e color)
{
      nMotorEncoder[motorB] = 0;
      nMotorEncoder[motorC] = 0;

      if (color == colorRed)
      {
            //turns sorter to left direction
            motorControl(10,1,motorB);

            //powers conveyor belt to move the item to sorter
            motorControl(20,1,motorC);

            //makes conveyor go in opposite direction to reset for next package
            motorControl(20,-1,motorC);

            //resets sorter to center configuration
            motorControl(10,-1,motorB);
      }


      else if (color == colorBlue)
      {
            //powers conveyor belt to move the item to sorter
            motorControl(20,1,motorC);

            //makes conveyor go in opposite direction to reset for next package
            motorControl(20,-1,motorC);
      }

      else if (color == colorGreen)
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
