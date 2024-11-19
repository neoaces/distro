#pragma once
#include "types.h"
#include "main.h"

void flr_travel_loop(int degrees_rotation, state_t *state) {
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
	const int distances[3] = {2300, 1200, 2100};
	setMotorTarget(motorB, 7, 15);

	for (int i = 0; i < 3; i++) {
		flr_travel_loop(distances[i], state);
		flr_seek_color(colorGreen);
		wait1Msec(1000);
		flr_color_seek_rotate(colorBlack, true);
		flr_travel_loop(250, state);
		flr_seek_color(colorGreen);
		wait1Msec(5000);
		nMotorEncoder[motorD] = 0;
		motor[motorC] = motor[motorD] = 15;
		while(abs(nMotorEncoder[motorD]) <= 350){}
		motor[motorC] = motor[motorD] = 0;
		flr_color_seek_rotate(colorBlack, false);
		sensorReset(S2);
		sensorReset(S3);
		wait1Msec(1000);
	}
	flr_travel_loop(1600, state);
	setMotorTarget(motorB, 0, 15);
	state.mode = Standby; // Moves to delivery state when finished
}
