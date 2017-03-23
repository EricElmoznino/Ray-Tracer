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
    
    Ray3D(Point3D origin, Point3D direction);
    
    // Function for returning the position along the ray
    // for a given lambda.
    Point3D rayPosition(double lambda) const;
};

#endif
