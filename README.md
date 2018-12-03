# fractal
Mandelbrot set image generator

Generates an image with the Mandelbrot set on the specified coordinates, using multithreading

make to compile

make clean to remove .o files and the executable

Usage: mandelbrot \<image width> \<image height> \<starting x> \<ending x> \<starting y> \<ending y> \<number of threads>

Suggestion: mandelbrot 1000 1000 -1.5 0.5 -1.0 1.0 10
