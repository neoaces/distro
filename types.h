#pragma once

typedef enum Colors {
	None = 0,
	Yellow = 1,
} cube_e;

typedef struct SystemState {
	int mode; // Refers to either startup, restock, delivery, or end_shift.
	cube_e stack[6]; // TODO: update with new data structure.
} state_t;

void init_state(state_t &state) {
	state.mode = 0; // Enters standby mode.

	for (int i = 0; i < 6; i++) {
		state.stack[i] = None;
	}
}
