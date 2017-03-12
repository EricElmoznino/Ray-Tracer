#ifndef Ray3D_h
#define Ray3D_h

#include <stdio.h>
#include "../GeometricTypes/Point3D.h"

// forward declare the object type to avoid circular dependencies
class Object3D;

class Ray3D {
public:
    Point3D origin;
    Point3D direction;
    
    // Function for returning the position along the ray
    // for a given lambda.
    Point3D rayPosition(Ray3D ray, double lambda);
    
    // Transforms a ray using the inverse transform for the specified object. This is so that we can
    // object intersection test for the canonical object
    Ray3D rayTransform(const Object3D &obj) const;
};

#endif
