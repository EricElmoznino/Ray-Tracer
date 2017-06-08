//
//  Torus.hpp
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-08.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#ifndef Torus_h
#define Torus_h

#include "../Object3D.h"
#include <stdio.h>

class Torus : public Object3D {
    const double R = 1.0;
    const double r = 0.5;
    
    ColourRGB colourAtLocalPoint(const Point3D &p) const;
    
    Point3D normalAtPoint(Point3D p) const;
    
public:
    Torus(const Material &material, const ColourRGB &colour);
    
    Intersection intersect(const Ray3D &ray);
    
    bool doesIntersect(const Ray3D &ray);
};

#endif /* Torus_h */
