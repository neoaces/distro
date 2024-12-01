#pragma once

// enum States
// This enum, states_e, represents the state of the robot at any given moment.
// We use the state in the global configuration struct and use the state
// along with a jump table that decides the logic required for the current state.
typedef enum States {
	Standby = 0,
	Restock = 1,
	End_Shift = 2,
	Route = 3,
} states_e;

// enum Colors
// The colors define the destination for the robot, which flr_route() uses.
// When the destination is None, then it returns to the loading bay.
// These also refer to the array positions of the colors in their stacks.
typedef enum Colors {
	None = 0,
	Green = 1,
	Yellow = 2,
	Red = 3,
} color_e;

// struct SystemState
// This struct represents the global state of the robot at any time.
// See Data Layout for more information
typedef struct SystemState {
	states_e mode;
	int stack[3][2]; // Used to index the pieces as they come in.
} state_t;

// void init_state(state_t &state)
// Used to initialize the global state.
// * NOTE: We take into account that upon creation, stack is initialized with all 0s.
// 		   0, in this case, represents the absence of a block in that slot.
void init_state(state_t &state) {
	state.mode = Standby; // Set the initial state to the standby state.
}
