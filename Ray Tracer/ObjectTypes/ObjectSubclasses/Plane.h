#ifndef Plane_h
#define Plane_h

#include "../Object3D.h"
#include <stdio.h>

class Plane : public Object3D {
protected:
    ColourRGB colourAtLocalPoint(const Point3D &p) const;
    
public:
    Plane(const AlbedosPhong &albedos, const ColourRGB &colour,
          double alpha, double refractionIndex, double shinyness);
    
    void intersect(const Ray3D &ray, double *lambda,
                   Point3D *intersection, Point3D *normal,
                   ColourRGB *colour) const;
};

#endif
