//
//  Cube.h
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-07.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#ifndef Cube_h
#define Cube_h

#include "../Object3D.h"
#include <stdio.h>

class Cube : public Object3D {
    const Point3D centre = Point3D(0, 0, 0, false);
    const double radius = 1.0;
    const double height = 2.0;
    
    ColourRGB colourAtLocalPoint(const Point3D &p) const;
    
public:
    Cube(const Material &material, const ColourRGB &colour);
    
    Intersection intersect(const Ray3D &ray);
    
    bool doesIntersect(const Ray3D &ray);
};

#endif /* Cube_h */
