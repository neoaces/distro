#include "follower.h"
#include "indexing.h"
#include "main.h"
#include "ui.h"
#include "types.h"

// void runLoop(state_t &state)
// state: The global state struct
// After the robot is initialized inside task main(), runLoop acts as a jump table, and delegates
// execution to the appropriate state function for the current state.

void runLoop(state_t &state) {
	// STANDBY MODE: await RESTOCK or END_SHIFT command
	if (state.mode == Standby) {
		ui_standby(state);
	}

	// RESTOCK MODE: robot indexes items
	else if (state.mode == Restock) {
		ind_loading(state);
	}

	// END_SHIFT MODE: call shutdown procedure
	else if (state.mode == End_Shift) {
		shutdown();
	}

	// ROUTE MODE: routing and line following
	else if (state.mode == Route) {
		flr_route(state);
	}
}
 
// task killSwitch()
// Our robot, given that it is the only robot during the demo, we decided that a physical e-stop 
// would be beneficial by helping us immediately stop execution, and allowed us to test our robot 
// faster. It relies on a touch sensor, easily accessible on the top of the robot, to stop
// execution.

task killSwitch() {
	while(!getTouchValue(S1)){}
	stopAllTasks();
}

// task main()
// Logic is kept to a minimum in here. Other than initializing the states, the main() function calls
// runLoop(state_t &state), which delegates the execution to the appropriate state function.

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
