//
//  Cone.h
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-07.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#ifndef Cone_h
#define Cone_h

#include "../Object3D.h"
#include <stdio.h>

class Cone : public Object3D {
    ColourRGB colourAtLocalPoint(const Point3D &p) const;
    
public:
    Cone(const Material &material, const ColourRGB &colour);
    
    Intersection intersect(const Ray3D &ray);
    
    bool doesIntersect(const Ray3D &ray);
};

#endif /* Cone_h */
