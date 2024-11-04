//#include "ui.h"

string StandbyStates[2] = {"Restock", "End Shift"};

typedef struct SystemState {
	int mode; // Refers to either startup, restock, delivery, or end_shift.
} state_t;

void ui_display_lines(ubyte n, string *elements, ubyte selected) { // NOTE: 8 possible text lines
	for (int i = 0; i < n; i++) {
		if (i == selected) {
			displayTextLine(8 - (n - i), "> %s", elements[i]);
		} else {
			displayTextLine(8 - (n - 1), "%s", elements[i]);
		}
	}
}

// Displays two choices on screen in standby: Restock or End Shift
void ui_get_standby_state(state_t &state) {
	string input;
	int temp_mode, selection;

	while (strcmp(input, "")) {
		while (getButtonPress(buttonEnter) != true) {
			// Put in here to code to display on screen.
			ui_display_lines(2, StandbyStates, );
		}
	}

	state.mode = temp_mode;
}

void runLoop(state_t &state) {
	// STANDBY MODE: await RESTOCK or END_SHIFT command
	ui_get_standby_state(state);
}

task main() {
	state_t state;
	state.mode = 0;
	runLoop(state);
}
