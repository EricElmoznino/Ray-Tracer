#!/bin/sh

# build
g++ -O4 -g svdDynamic.c RayTracer.c utils.c -lm -o RayTracer

# run: size, depth, antialiasing, name
./RayTracer 300 3 1 RenderedImage.ppm

# open the rendered image
open RenderedImage.ppm
