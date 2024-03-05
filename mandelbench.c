#include <stdio.h>

#ifndef DIFFICULTY
#define DIFFICULTY 8
#endif

#if DIFFICULTY > 8*(4)-2
#error "Difficulty is too high, can't perform fixed-point calcs"
#endif

// Using fixed-point arithmetic with 2 bits whole part + 6 bits fractional part
// aka, every number is represented as 2^6 times its true value
int mandel8_is_bounded(const int real, const int imag, const int max_iter) {
    int realpos = 0;
    int imagpos = 0;
    for(int i = 0; i < max_iter; i++) {
        int newreal = ((realpos*realpos) >> (DIFFICULTY - 2))
                 - ((imagpos*imagpos) >> (DIFFICULTY - 2)) + real;
        // Because shifting a negative rounds toward -inf, there's some added
        // nonsense here to correct to round toward 0
        int bias = (realpos*imagpos) < 0 ? ((1 << (DIFFICULTY - 3)) - 1) : 0;
        int newimag = ((realpos*imagpos + bias) >> (DIFFICULTY - 3)) + imag;
        // All points outside -2...2 are unbounded
        if(newreal > (1 << (DIFFICULTY - 1)) 
                || newreal < -(1 << (DIFFICULTY - 1))
                || newimag > (1 << (DIFFICULTY - 1))
                || newimag < -(1 << (DIFFICULTY - 1))) {
            return 0;
        }
        realpos = newreal;
        imagpos = newimag;
    }
    return 1;
}

int main(int argc, char** argv) {
    for(int y = (1 << (DIFFICULTY - 1)) - 1;
            y >= -(1 << DIFFICULTY); y--) {
        for(int x = -(1 << DIFFICULTY); x < (1 << DIFFICULTY); x += 8) {
            int acc = 0;
            for(int i = 0; i < 8; i++) {
                int bit = mandel8_is_bounded(x + i, y, 10000);
                acc <<= 1;
                acc += bit;
            }
            printf("%02x", acc);
        }
    }
}