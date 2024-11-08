#include "follower.h"
#include "main.h"
#include "ui.h"
#include "types.h"


// TODO: Determine next actions based on the state of the robot in this function
// 			 Consider a simple match statement.
void runLoop(state_t &state) {
	// STANDBY MODE: await RESTOCK or END_SHIFT command
	if (state.mode == 0) {
		state.mode = ui_get_standby_state(state);
	}

	// RESTOCK MODE: robot indexes items
	else if (state.mode == 1) {

	}

	// ENDSHIFT MODE: call shutdown procedure
	else if (state.mode == 2) {
		shutdown();
	}

	// ROUTE MODE: routing and line following
	else if (state.mode == 3) {
		flr_route(state);
	}

	// DELIVER: moving box off robot
	else if (state.mode == 2) {

	}
}

task main() {
	state_t state;
	init_state(state);

	while (state.mode != -1) {
		runLoop(state);
	}
}
