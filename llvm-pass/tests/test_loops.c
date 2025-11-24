// test_loops.c
// Simple test program to exercise MyOptimizer loop unroll hints.

int sum_fixed_loop(int n) {
    int s = 0;
    // Small fixed trip-count loop - ideal for unrolling.
    for (int i = 0; i < 4; ++i) {
        s += n;
    }
    return s;
}

int sum_variable_loop(int n) {
    int s = 0;
    // Variable trip-count loop - LLVM may handle this differently.
    for (int i = 0; i < n; ++i) {
        s += i;
    }
    return s;
}
