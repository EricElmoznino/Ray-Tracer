#ifndef Ray3D_h
#define Ray3D_h

#include <stdio.h>
#include "../GeometricTypes/Point3D.h"

class Ray3D {
public:
    Point3D origin;
    Point3D direction;
    // Function for returning the position along the ray
    // for a given lambda.
    Point3D rayPosition(Ray3D ray, double lambda);
    
};

#endif
