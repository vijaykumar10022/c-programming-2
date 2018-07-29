#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);

int main() {
    if (power(4, 4) != 256) {
        return EXIT_FAILURE;
    }
//    if (power(-2, 1) != -2) {
//        return EXIT_FAILURE;
//    }
    if (power(0, 1) != 0) {
	return EXIT_FAILURE;
    }
    if (power(30, 1) != 30) {
	return EXIT_FAILURE;
    }
    if (power(4, 0) != 1) {
	return EXIT_FAILURE;
    }
    if (power(256, 2) != 65536) {
	return EXIT_FAILURE;
    }
    if (power(0, 0) != 1) {
	return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
