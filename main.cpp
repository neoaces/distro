#include "follower.h"
#include "indexing.h"
#include "main.h"
#include "ui.h"
#include "types.h"


void runLoop(state_t &state) {
	// STANDBY MODE: await RESTOCK or END_SHIFT command
	if (state.mode == 0) {
		ui_standby(state);
	}

	// RESTOCK MODE: robot indexes items
	else if (state.mode == 1) {
		ind_loading(state);
	}

	// END_SHIFT MODE: call shutdown procedure
	else if (state.mode == 2) {
		shutdown();
	}

	// ROUTE MODE: routing and line following
	else if (state.mode == 3) {
		flr_route(state);
	}

	// DELIVER: moving box off robot
	else if (state.mode == 4) {
		//dvr_deliver(state);
	}
}

task killswitch() {
	while(!getTouchValue(S1)){}
	stopAllTasks();
}

task main() {
	init_program(); // Initializes system
	state_t state;
	init_state(state); // Initializes global system state
	SensorType[S1] = sensorEV3_Touch;
	wait1Msec(50);

	startTask(killswitch);

	while (state.mode != -1) {
		runLoop(state);
	}
}
