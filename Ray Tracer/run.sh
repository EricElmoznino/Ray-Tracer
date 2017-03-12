#!/bin/sh

# build
sh compile.sh

# run: size, depth, antialiasing, name
./RayTracer 300 3 1 RenderedImage.ppm

# open the rendered image
open RenderedImage.ppm
