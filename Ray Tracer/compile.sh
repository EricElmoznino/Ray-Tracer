#!/bin/sh
g++ -O4 -g svdDynamic.c RayTracer.cpp utils.c Point3D.cpp Transform3D.cpp Plane.cpp Sphere.cpp Image.cpp Ray3D.cpp AlbedosPhong.cpp Object3D.cpp -lm -o RayTracer
