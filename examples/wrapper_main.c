// Week 3 wrapper_main.c
// Simple C wrapper that calls the LLVM IR run() function.

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    void run(void);
#ifdef __cplusplus
}
#endif

int main(void) {
    run();
    return 0;
}