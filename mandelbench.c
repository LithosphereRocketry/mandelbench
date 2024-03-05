#include <stdio.h>

#ifndef DIFFICULTY
#define DIFFICULTY 8
#endif

#if DIFFICULTY > 8*(4)-2
#error "Difficulty is too high, can't perform fixed-point calcs"
#endif

// Using fixed-point arithmetic with 2 bits whole part + (N-2) bits fractional part
// aka, every number is represented as 2^(N-2) times its true value
int mandel_is_bounded(const int real, const int imag, const int max_iter) {
    int realpos = 0;
    int imagpos = 0;
    for(int i = 0; i < max_iter; i++) {
        int newreal = ((realpos*realpos) >> 6)
                 - ((imagpos*imagpos) >> 6) + real;
        int newimag = ((2*realpos*imagpos) >> 6) + imag;
        // All points outside -2...2 are unbounded
        if(newreal > (1 << 7) 
                || newreal < -(1 << 7)
                || newimag > (1 << 7)
                || newimag < -(1 << 7)) {
            return 0;
        }
        realpos = newreal;
        imagpos = newimag;
    }
    return 1;
}

int main(int argc, char** argv) {
    for(int y = ((1 << 7) - 1); 
                y >= -(1 << 7); y--) {
        for(int x = -(1 << 7);
                    x < (1 << 7); x += 8) {
            int acc = 0;
            for(int i = 0; i < 8; i++) {
                int bit = mandel_is_bounded(x + i, y, 105);
                acc <<= 1;
                acc += bit;
            }
            printf("%02x", acc);
        }
    }
}