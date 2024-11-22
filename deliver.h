#pragma once
#include "types.h"
#include "main.h"
// UNUSED.
void dvr_deliver(state_t &state) {
	// UNIMPLEMENTED: Align and drive robot into bay.
	// Once aligneds

	for (int i = 0; i < 3; i++) {
		if (peek_stack(state, (color_e) i) != 0) {
			// There are remaining packages. Deliver next package.
			state.destination = (color_e) i;
			state.mode = Route;
			return;
		}
	}

	// There are no packages left. Return to standby.
	state.destination = None;
	state.mode = Route;
}
