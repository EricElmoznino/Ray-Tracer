#ifndef Plane_h
#define Plane_h

#include "../Object3D.h"
#include <stdio.h>

class Plane : public Object3D {
protected:
    ColourRGB colourAtLocalPoint(const Point3D &p) const;
    
public:
    Plane(const Material &material, const ColourRGB &colour);
    
    Intersection intersect(const Ray3D &ray);
};

#endif
