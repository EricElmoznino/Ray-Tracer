#!/bin/sh
g++ -std=c++11 -O4 -g -fopenmp main.cpp GeometricTypes/svdDynamic.cpp RayTracer.cpp GeometricTypes/Point3D.cpp GeometricTypes/Transform3D.cpp ObjectTypes/ObjectSubclasses/Plane.cpp ObjectTypes/ObjectSubclasses/Sphere.cpp ObjectTypes/ObjectSubclasses/PlaneLightSource.cpp ObjectTypes/Image.cpp Lights/Light.cpp Lights/PointLightSource.cpp Lights/AreaLightElement.cpp ObjectTypes/ColourRGB.cpp ObjectTypes/Ray3D.cpp ObjectTypes/Material.cpp ObjectTypes/Object3D.cpp View.cpp Skybox.cpp Utilities/ProgressManager.cpp -lm -o RayTracer
