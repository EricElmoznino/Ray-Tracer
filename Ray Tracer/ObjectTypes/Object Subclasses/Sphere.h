#ifndef Sphere_h
#define Sphere_h

#include "Object3D.h"
#include <stdio.h>

class Sphere : public Object3D {
public:
    void intersect(const Ray3D &ray, double *lambda,
                   Point3D *intersection, Point3D *normal,
                   double *a, double *b);
};

#endif
