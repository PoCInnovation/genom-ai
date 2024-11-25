unsigned int xor_seed = 12345; // Set to a random number in main

unsigned int xorshift32() {
    xor_seed ^= xor_seed << 13;
    xor_seed ^= xor_seed >> 17;
    xor_seed ^= xor_seed << 5;
    return xor_seed;
}
