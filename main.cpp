#include "ui.h"

// TODO: Determine next actions based on the state of the robot in this function
// 			 Consider a simple match statement.
void runLoop(state_t &state) {
	// STANDBY MODE: await RESTOCK or END_SHIFT command
	ui_get_standby_state(state);
}

task main() {
	state_t state;
	init_state(state);
	runLoop(state);

	delay(5000); // TEMPORARY: 11/4
}
