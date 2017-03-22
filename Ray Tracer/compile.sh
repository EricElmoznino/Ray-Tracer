#!/bin/sh
g++ -std=c++11 -O4 -g main.cpp GeometricTypes/svdDynamic.c RayTracer.cpp GeometricTypes/Point3D.cpp GeometricTypes/Transform3D.cpp ObjectTypes/ObjectSubclasses/Plane.cpp ObjectTypes/ObjectSubclasses/Sphere.cpp ObjectTypes/Image.cpp PointLightSource.cpp ObjectTypes/ColourRGB.cpp ObjectTypes/Ray3D.cpp ObjectTypes/Material.cpp ObjectTypes/Object3D.cpp View.cpp -lm -o RayTracer
