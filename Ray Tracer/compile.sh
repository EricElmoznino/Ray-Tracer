#!/bin/sh
g++ -O4 -g svdDynamic.c RayTracer.cpp utils.c Point3D.cpp Transform3D.cpp -lm -o RayTracer
