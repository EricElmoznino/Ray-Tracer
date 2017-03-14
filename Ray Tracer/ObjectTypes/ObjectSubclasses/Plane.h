#ifndef Plane_h
#define Plane_h

#include "../Object3D.h"
#include <stdio.h>

class Plane : public Object3D {
public:
    Plane(const AlbedosPhong &albedos, const ColourRGB &colour,
          double alpha, double refractionIndex, double shinyness);
    
    void intersect(const Ray3D &ray, double *lambda,
                   Point3D *intersection, Point3D *normal,
                   double *a, double *b) const;
};

#endif
