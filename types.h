#pragma once

typedef struct SystemState {
	int mode; // Refers to either startup, restock, delivery, or end_shift.
} state_t;

void init_state(state_t &state) {
	state.mode = 0;
}
