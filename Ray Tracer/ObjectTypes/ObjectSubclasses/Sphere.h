#ifndef Sphere_h
#define Sphere_h

#include "../Object3D.h"
#include <stdio.h>

class Sphere : public Object3D {
protected:
    ColourRGB colourAtLocalPoint(const Point3D &p) const;
    
public:
    Sphere(const Material &material, const ColourRGB &colour);
    
    Intersection intersect(const Ray3D &ray) const;
};

#endif
