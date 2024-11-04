void increment(ubyte &n, ubyte limit);
	if ((ubyte) (n + 1) > limit) {
		n = 0;
	} else {
		n += 1;
	}
}
