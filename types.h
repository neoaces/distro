#pragma once

// This enum, states_e, represents the state of the robot at any given moment.
// We use the state in the global configuration struct and use the state
// along with a jump table that decides the logic required for the current state.
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
	None = 0,
	Black = 1,
	Green = 3,
	Yellow = 4,
	Red = 5,
} color_e;

typedef struct SystemState {
	states_e mode; // Refers to either startup, restock, delivery, or end_shift.
	int stack[3][2]; //Used to index the pieces as they come in.
} state_t;

void init_state(state_t &state) {
	state.mode = Standby; // Set the initial state to the standby state.
}
