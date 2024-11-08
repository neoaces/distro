#pragma once
#include "types.h"
#include "main.h"

void flr_route(state_t &state) {
	// NOTE: There is no need to change the destination in this function. Next destination will be changed by the init function and the delivery function.
	// This is because delivery will choose dest. based on whether there are products remaining.


	state.mode = Deliver; // Moves to delivery state when finished
}
