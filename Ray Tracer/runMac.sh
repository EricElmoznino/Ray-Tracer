#!/bin/sh

# build
sh compileMac.sh

# run: size, depth, antialiasing, name
./RayTracer 1080 3 1 RenderedImage.ppm

# open the rendered image
if [ "$(uname -s)" == "Darwin" ]; then
	open RenderedImage.ppm
elif [ "$(uname -s)" == "MINGW64_NT-10.0" ]; then
	start RenderedImage.ppm
fi
