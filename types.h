#pragma once

typedef enum States {
	Standby = 0,
	Restock = 1,
	End_Shift = 2,
	Route = 3,
	Deliver = 4,
} states_e;

typedef enum Colors {
	None = 0,
	Yellow = 1,
} color_e;

typedef struct SystemState {
	states_e mode; // Refers to either startup, restock, delivery, or end_shift.
	color_e stack[6]; // TODO: update with new data structure.
} state_t;

void init_state(state_t &state) {
	state.mode = 0; // Enters standby mode.

	for (int i = 0; i < 6; i++) {
		state.stack[i] = None;
	}
}
