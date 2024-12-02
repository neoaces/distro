#pragma once
#include "types.h"

// void ind_loading(state_t &state) - ADITYYA KAUSHAL, MARK TRETIAKOV
// All in one function that performs indexing and sorting.
// ALGORITHM:
// 1. Based on colour of block, switch sorter to desired position
// 2. Drives towards the next block.
// 3. Picks up the next block

void ind_loading(state_t &state) {
	// Resets indexer
	motor[motorA] = -25;
	wait1Msec(750);
	motor[motorA] = 0;

	for(int i = 0; i < 6; i++) {
		// 1. 
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
		
		// 2.
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

		// 3.
		motor[motorA] = -25;
		wait1Msec(500);
		motor[motorA] = 0;
		wait1Msec(1000);
	}

	state.mode = Route;
}
