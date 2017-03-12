#!/bin/sh
g++ -O4 -g GeometricTypes/svdDynamic.c RayTracer.cpp utils.c GeometricTypes/Point3D.cpp GeometricTypes/Transform3D.cpp ObjectTypes/ObjectSubclasses/Plane.cpp ObjectTypes/ObjectSubclasses/Sphere.cpp ObjectTypes/Image.cpp ObjectTypes/Ray3D.cpp ObjectTypes/AlbedosPhong.cpp ObjectTypes/Object3D.cpp -lm -o RayTracer
