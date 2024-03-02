#include <stdio.h>

// Using fixed-point arithmetic with 2 bits whole part + 6 bits fractional part
// aka, every number is represented as 2^6 times its true value
int mandel8_is_bounded(const int real, const int imag, const int max_iter) {
    int realpos = 0;
    int imagpos = 0;
    for(int i = 0; i < max_iter; i++) {
        int newreal = (realpos*realpos) / 64 - (imagpos*imagpos) / 64 + real;
        int newimag = 2*realpos*imagpos / 64 + imag;
        // All points outside -2...2 are unbounded
        if(newreal > 2*64 || newreal < -2*64 || newimag > 2*64 || newimag < -2*64) {
            return 0;
        }
        realpos = newreal;
        imagpos = newimag;
    }
    return 1;
}

int main(int argc, char** argv) {
    for(int y = 127; y >= -128; y--) {
        for(int x = -128; x < 128; x += 8) {
            int acc = 0;
            for(int i = 0; i < 8; i++) {
                int bit = mandel8_is_bounded(x + i, y, 105);
                acc <<= 1;
                acc += bit;
            }
            printf("%02x", acc);
        }
    }
}