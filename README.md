# mandelbench
 A fixed-point computational benchmark program for homebrew CPU designs.
 Designed to run on a very wide range of hardware. 

## Implementing Mandelbench

This benchmark generates a 1-bit-depth rendering of the Mandelbrot set. The
resultant data should be placed in stdout (for implementations using an OS
interface) or printed over the hardware's native output port.

The difficulty of the benchmark is set by the number of bits in the X and Y
dimensions of the image generated; the dimensions are always equal and always
a power of two. The output of the program should be formatted as a continuous
string of human-readable hexadecimal in the system's default character encoding.
Each pixel of the image corresponds to one bit of the returned data, with 1
representing a value that stays bounded and 0 representing a value that escapes
to infinity. Pixels are scanned left-to-right, top-to-bottom, with the most
significant bit of a hexadecimal digit representing the leftmost pixel in that
line of 4.

An example output image for a mandel3 program might look like this:
```
#...###.
##..#...
........
..###...
..###...
..###...
........
#####...
```
This should be returned as the console output:
```
8ec80038383800f8
```

The fractal should be rendered such that the leftmost and bottommost bounds of
the region correspond to real and imaginary values of -2, and the topmost and
rightmost correspond to real and imaginary values of 2 minus one LSB. For
example, mandel8's output ranges -2 - 2i to (2 - 1/64) + (2 - 1/64)i.

### Restrictions

In order to ensure Mandelbench is a useful benchmark, certain restrictions are
placed on how the set is calculated.
* The data may not be precomputed and loaded from external storage.
* The code may not take advantage of properties such as axis-symmetry; each
pixel must be computed individually.
* Escaping results may be discarded once they exceed -2 <= real <= (2 - LSB)
or -2 <= imag <= (2 - LSB).

## Reference Implementation & MandelView

A reference C implementation of mandel8 is provided in this repository, along
with a small tool called MandelView. MandelView takes a hexadecimal string as
specified by the benchmark via standard input and displays a simple graphical
rendering of the data.

### Building
To build the reference implementation, run `make` or `make bench`; to build only
the viewer, run `make view`; to build both, run `make all`. Note that the viewer
requires that the SDL2 development libraries be installed on your system.

MandelView can be used to show the output of the reference benchmark as follows:
```sh
./mandel8 | ./mandelview
```

Or it can be used to show the result of a previous computation as follows:
```sh
./mandelview < myfile.hex
```

Your implementation can be tested against the reference as follows:
```sh
./your-cool-processor > myfile.hex
./mandel8 > reference.hex
cmp myfile.hex reference.hex
```