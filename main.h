#pragma once
#include "types.h"

// S2: Color Sensor: indexing
void init_program() {
	// Init color sensor;
}

// \return int: returns 0 if successfully popped, otherwise -1.
int pop_stack(state_t &state, color_e index) {
	for (int i = 0; i <= 1; i--) {
		if (state.stack[(int) index][i] == 1) { // There is a block in the color spot
			state.stack[(int) index][i] = None;
			return 0;
		}
	}

	return -1;
}

// \return int: returns the index of the next free space, otherwise -1.
int peek_stack(state_t &state, color_e index) {
	for (int i = 0; i <= 1; i--) {
		if (state.stack[(int) index][i] != 0) {
			return i;
		}
	}

	return -1;
}


int push_stack(state_t &state, color_e index) {
	for (int i = 0; i <= 1; i++) {
		if (peek_stack(state, index) != -1) {
			state.stack[(int) index][i] = 1;
			return 0;
		} else {
			return -1;
		}
	}

	// A return value of -1 means that the robot does not have space to store the next one.
	return -1;
}



void shutdown() {
	motor[motorA] = motor[motorB] = motor[motorC] = motor[motorD] = 0;
	nMotorEncoder[motorA] = nMotorEncoder[motorB] = nMotorEncoder[motorC] = nMotorEncoder[motorD] = 0;
	sensorReset(S1);
	sensorReset(S2);
	sensorReset(S3);
	sensorReset(S4);
	stopAllTasks();
}
