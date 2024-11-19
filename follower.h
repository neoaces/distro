#pragma once
#include "types.h"
#include "main.h"

void flr_travel_loop(int rotations, state_t *state) {
	// TODO: Switch mode to reflected.
	const float kp = 0.2;
	const float kd = 0.01;
	float last_error = 0, error = 0, derivative = 0, correction = 0, base_speed = -25;

	nMotorEncoder[motorC] = 0;

	while(abs(nMotorEncoder[motorC]) < rotations) {
		error = getColorReflected(S3) - getColorReflected(S2);

		// Note: we want to take away the change in error as to decrease the effect of the derivative, thus they are switched
		derivative = error - last_error;
		correction = kp * error + kd * derivative;

		motor[motorC] = base_speed + correction;
		motor[motorD] = base_speed - correction;
		last_error = error;
	}
}

void flr_seek_color(color_e color, state_t *state) {
	// TODO: Switch mode to color.
	int required = 0;
	switch (color) {
		case Red:
			required = colorRed;
			break;
		case Green:
			required = colorGreen;
			break;
		case Yellow:
			required = colorYellow;
			break;
	}

	while (getColorName(S3) != required) {
		motor[motorC] = 10;
		motor[motorD] = 10;
	}
}

void flr_route(state_t &state) {
	const int distances[4] = {1500, 1500, 1500, 1500};

	for (int i = 0; i < 4; i++) {
		flr_travel_loop(distances[i], state);
	}

	state.mode = Deliver; // Moves to delivery state when finished
}
