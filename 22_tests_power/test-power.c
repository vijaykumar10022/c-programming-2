unsigned power(unsigned x, unsigned y);

int main() {
    if (power(4, 4) != 256) {
        return EXIT_FAILURE;
    }
    if (power(-2, 1) != -2) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
