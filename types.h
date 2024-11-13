#pragma once

typedef enum States {
	Standby = 0,
	Restock = 1,
	End_Shift = 2,
	Route = 3,
	Deliver = 4,
} states_e;

// The colors define the destination for the robot, which flr_route() uses.
// When the destination is None, then it returns to the loading bay.
// These also refer to the array positions of the colors in their stacks.
typedef enum Colors {
	None = -1,
	Red = 0,
	Blue = 1,
	Green = 2,
} color_e;

typedef struct SystemState {
	states_e mode; // Refers to either startup, restock, delivery, or end_shift.
	int stack[3][2]; // TODO: update with new data structure.
	color_e destination;
} state_t;

void init_state(state_t &state) {
	state.mode = Standby; // Enters standby mode.
}
