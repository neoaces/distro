#pragma once
#include "types.h"

// Route: during journey, moving to delivery bay or during return trip
// TODO: define all the pathfinding logic when robot is in this state.
// Deliver: aligns robot to bay, moves objects off the robot

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

void ui_display_lines(ubyte n, string *elements, ubyte& selected) { // NOTE: 8 possible text lines
	for (ubyte i = 0; i < n; i++) {
		if (i == selected) {
			displayTextLine(5, "> %s", elements[i]);
			displayTextLine(5, "> %s", elements[i]);
		} else {
			displayTextLine(5, "%s", elements[i]);
			displayTextLine(5, "%s", elements[i]);
		}
	}
}

// Displays two choices on screen in standby: Restock or End Shift
ubyte ui_get_selection(state_t &state, int n, string *selections) {
	ubyte selected = 0;

	while (true) {
		ui_display_lines(1, selections, selected);

		//if (getButtonPress(buttonEnter)== true) {
			//while(getButtonPress(buttonEnter) == true) {}; // Wait for release of button
			//return selected;
		//}

		//if (getButtonPress(buttonUp)== true) {
			//while(getButtonPress(buttonUp) == true) {}; // Wait for release of button
			//increment(selected, n);
		//}

		//if (getButtonPress(buttonDown)== true) {
			//while(getButtonPress(buttonDown) == true) {}; // Wait for release of button
			//decrement(selected, n);
		//}
	}

	return 0;
}

states_e ui_get_standby_state(state_t &state) {
	return (states_e) ui_get_selection(state, 1, StandbyStates) + 1; // Accounts for offset in mode representation
}

void ui_standby(state_t &state) {
	displayCenteredTextLine(3, "Right Button > Run");
	displayCenteredTextLine(4, "Left Button > Shutdown");
	while(true) {
		if(getButtonPress(buttonRight)) {
			eraseDisplay();
			displayCenteredTextLine(3, "Right Button > Confirm");
			displayCenteredTextLine(4, "Left Button > Deny");
			wait1Msec(500);
			while(!getButtonPress(buttonRight) && !getButtonPress(buttonLeft)) {}
			if (getButtonPress(buttonRight)) {
				eraseDisplay();
				displayCenteredTextLine(3, "Running Route");
				state.mode = Restock;
				wait1Msec(3000);
				return;
			} else if (getButtonPress(buttonLeft)) {
				eraseDisplay();
				displayCenteredTextLine(3, "Right Button > Run");
				displayCenteredTextLine(4, "Left Button > Shutdown");
				wait1Msec(500);
			}
		} else if(getButtonPress(buttonLeft)) {
			eraseDisplay();
			displayCenteredTextLine(3, "Right Button > Confirm");
			displayCenteredTextLine(4, "Left Button > Deny");
			wait1Msec(500);
			while(!getButtonPress(buttonRight) && !getButtonPress(buttonLeft)) {}
			if (getButtonPress(buttonRight)) {
				eraseDisplay();
				displayCenteredTextLine(3, "Shutting Down");
				wait1Msec(3000);
				state.mode = End_Shift;
				return;
			} else if (getButtonPress(buttonLeft)) {
				eraseDisplay();
				displayCenteredTextLine(3, "Right Button > Run");
				displayCenteredTextLine(4, "Left Button > Shutdown");
				wait1Msec(500);
			}
		}
	}
}
