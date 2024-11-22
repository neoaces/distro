#pragma once
#include "types.h"
#include "main.h"

void flr_travel_loop(int degrees_rotation, state_t *state) {
	// We use a PD controller to control our line follower.
	// NOTE: We do not include an I term because in our testing, we experienced integral windup.
	const float kp = 0.3;
	const float kd = 0.01;
	float last_error = 0, error = 0, derivative = 0, correction = 0, base_speed = -15;

	nMotorEncoder[motorC] = 0;
	nMotorEncoder[motorD] = 0;

	while(abs(nMotorEncoder[motorC]) < degrees_rotation && abs(nMotorEncoder[motorC]) < degrees_rotation) {
		error = getColorReflected(S3) - getColorReflected(S2);

		// Note: we want to take away the change in error as to decrease the effect of the derivative, thus they are switched
		derivative = error - last_error;
		correction = kp * error + kd * derivative;

		motor[motorC] = base_speed + correction;
		motor[motorD] = base_speed - correction;
		last_error = error;
	}
}

void flr_seek_color(int color) {

	motor[motorC] = motor[motorD] = -10;
	while (getColorName(S3) != color && getColorName(S2) != color) {
	}
	motor[motorC] = motor[motorD] = 0;
}

void flr_color_seek_rotate(int color, bool is_turning_left) {
	nMotorEncoder[motorC] = 0;

	if(!is_turning_left) {
		motor[motorC] = 10;
		motor[motorD] = -10;
		while(abs(nMotorEncoder[motorC]) <= 80){};
		motor[motorC] = 5;
		motor[motorD] = -5;
		while (getColorName(S2) != color) {
		}
	} else {
		motor[motorC] = -10;
		motor[motorD] = 10;
		while(abs(nMotorEncoder[motorC]) <= 80){};
		motor[motorC] = -5;
		motor[motorD] = 5;
		while (getColorName(S3) != color) {
		}
	}
	motor[motorC] = motor[motorD] = 0;
}

void flr_route(state_t &state) {
	const int distances[3] = {2000, 1200, 2100};
	setMotorTarget(motorB, 7, 15);

	for (int i = 0; i < 3; i++) {
		/*
		/  1. Travel from bay to bay,
		*/
		flr_travel_loop(distances[i], state); // Travel the loop for the measured distance.
		flr_seek_color(colorRed); // The color of the unloading bay indicator is red, thus seek red after traveling along loop.
		wait1Msec(1000);

		/*
		/  2. Align to color
		*/
		flr_color_seek_rotate(colorBlack, true); // After aligning to the centre of the intersection, rotate towards to the bay.
		flr_travel_loop(250, state);
		flr_seek_color(colorRed);
		wait1Msec(2000);

		/*
		/  3. Return to loop for next traversal
		*/
		nMotorEncoder[motorD] = 0;
		motor[motorC] = motor[motorD] = 15;
		while(abs(nMotorEncoder[motorD]) <= 350){}
		motor[motorC] = motor[motorD] = 0;
		flr_color_seek_rotate(colorBlack, false);
		sensorReset(S2);
		sensorReset(S3);
		wait1Msec(1000);
	}

	// Return to loading bay
	flr_travel_loop(1600, state);
	setMotorTarget(motorB, 0, 15);
	motor[motorC] = motor[motorD] = 0;
	state.mode = Standby; // Moves to delivery state when finished
}
