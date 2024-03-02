# mandelbench
 A fixed-point computational benchmark program for homebrew CPU designs.
 Designed to run on a very wide range of hardware. 

## Implementing Mandelbench

This benchmark generates a 1-bit-depth rendering of the Mandelbrot set. The
resultant data should be placed in stdout (for implementations using an OS
interface) or printed over the hardware's native output port. The difficulty of
the benchmark 