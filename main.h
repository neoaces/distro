#pragma once
#include "types.h"

color_e pop(state_t &state) {
	int i = 0;

	for (int i = 5; i >= 0; i--) {
		if (state.stack[i] != 0) {
			color_e color = state.stack[i];
			return color;
		}
	}

	return None;
}

void shutdown() {


}
