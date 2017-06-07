//
//  Cylinder.h
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-06.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#ifndef Cylinder_h
#define Cylinder_h

#include "../Object3D.h"
#include <stdio.h>

class Cylinder : public Object3D {
    const Point3D centre = Point3D(0, 0, 0, false);
    const double radius = 1.0;
    const double height = 2.0;
    
    ColourRGB colourAtLocalPoint(const Point3D &p) const;
    
public:
    Cylinder(const Material &material, const ColourRGB &colour);
    
    Intersection intersect(const Ray3D &ray);
    
    bool doesIntersect(const Ray3D &ray);
};

#endif /* Cylinder_h */
