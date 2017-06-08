#!/bin/sh
gcc-6 -lstdc++ -std=c++11 -Ofast  -g -fopenmp *.cpp GeometricTypes/*.cpp ObjectTypes/*.cpp ObjectTypes/ObjectSubclasses/*.cpp Lights/*.cpp Utilities/*.cpp ML/*.cpp -lm -o RayTracer
