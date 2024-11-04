#pragma once
#include "types.h"

// Route: during journey, moving to delivery bay or during return trip
// TODO: define all the pathfinding logic when robot is in this state.
// Deliver: aligns robot to bay, moves objects off the robot
const string States[4] = {"Restock", "End Shift", "Route", "Deliver"};
const string StandbyStates[2] = {"Restock", "End Shift"};

void increment(ubyte &n, ubyte limit) {
	if ((ubyte) (n + 1) > limit) {
		n = 0;
	} else {
		n += 1;
	}
}

void decrement(ubyte &n, ubyte limit) {
	if ((n - 1) < 0) {
		n = limit;
	} else {
		n -= 1;
	}
}

void ui_display_lines(ubyte n, string *elements, ubyte selected) { // NOTE: 8 possible text lines
	for (ubyte i = 0; i < n; i++) {
		if (i == selected) {
			displayTextLine(8 - (n - i), "> %s", elements[i]);
		} else {
			displayTextLine(8 - (n - 1), "%s", elements[i]);
		}
	}
}

// Displays two choices on screen in standby: Restock or End Shift
ubyte ui_get_selection(state_t &state, int n, string *selections) {
	ubyte selected = 0;

	while (true) {
		ui_display_lines(n, selections, selected);

		if (getButtonPress(buttonEnter)== true) {
			while(getButtonPress(buttonEnter) == true) {}; // Wait for release of button
			return selected;
		}

		if (getButtonPress(buttonUp)== true) {
			while(getButtonPress(buttonUp) == true) {}; // Wait for release of button
			increment(selected, n);
		}

		if (getButtonPress(buttonDown)== true) {
			while(getButtonPress(buttonDown) == true) {}; // Wait for release of button
			decrement(selected, n);
		}
	}
}

ubyte ui_get_standby_state(state_t &state) {
	return ui_get_selection(state, 1, StandbyStates);
}
