#pragma once

int run_tests() {
	// State tests

	//
	// Take a stack a = [[1, 0], [1, 1], [0, 0].
	// This tells us there is one red block, two blue blocks, and no green blocks.

	// Test 1: Remove block
	// pop_stack(a, Red)
	// peek_stack(a, Red)
	// expected: -1, since there is no longer any blocks in red.

	// Test 2: Overflow
	// pop_stack(a, Green);
	// expected: -1, since there are no blocks in green.

	// Test 3: Take one block out
	// pop_stack(a, Blue);
	// peek_stack(a, Blue);
	// expected: 0, since there will be one block in green.

	return 0;
}
