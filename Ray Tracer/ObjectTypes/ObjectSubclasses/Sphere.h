#ifndef Sphere_h
#define Sphere_h

#include "../Object3D.h"
#include <stdio.h>

class Sphere : public Object3D {
protected:
    ColourRGB colourAtLocalPoint(const Point3D &p) const;
    
public:
    Sphere(const AlbedosPhong &albedos, const ColourRGB &colour,
           double alpha, double refractionIndex, double shinyness);
    
    void intersect(const Ray3D &ray, double *lambda,
                   Point3D *intersection, Point3D *normal,
                   ColourRGB *colour) const;
};

#endif
