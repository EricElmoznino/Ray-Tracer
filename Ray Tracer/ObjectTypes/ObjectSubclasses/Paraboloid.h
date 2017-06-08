//
//  Paraboloid.h
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-07.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#ifndef Paraboloid_h
#define Paraboloid_h

#include "../Object3D.h"
#include <stdio.h>

class Paraboloid : public Object3D {
    ColourRGB colourAtLocalPoint(const Point3D &p) const;
    
    Point3D normalAtPoint(Point3D p) const;
    
public:
    Paraboloid(const Material &material, const ColourRGB &colour);
    
    Intersection intersect(const Ray3D &ray);
    
    bool doesIntersect(const Ray3D &ray);
};

#endif /* Paraboloid_h */
