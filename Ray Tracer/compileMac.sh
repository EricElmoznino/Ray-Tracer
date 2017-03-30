#!/bin/sh
gcc-6 -lstdc++ -std=c++11 -Ofast -fopenmp -g -fopenmp *.cpp GeometricTypes/*.cpp ObjectTypes/*.cpp ObjectTypes/ObjectSubclasses/*.cpp Lights/*.cpp Utilities/*.cpp -lm -o RayTracer
