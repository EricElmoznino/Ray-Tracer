//
//  Disk.h
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-08.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#ifndef Disk_h
#define Disk_h

#include "../Object3D.h"
#include <stdio.h>

class Disk : public Object3D {
    const Point3D c = Point3D(0, 0, 0, false);
    const Point3D normal = Point3D(0, 0, 1, true);
    const double radius = 1.0;
    
    ColourRGB colourAtLocalPoint(const Point3D &p) const;
    
public:
    Disk(const Material &material, const ColourRGB &colour);
    
    Intersection intersect(const Ray3D &ray);
    
    bool doesIntersect(const Ray3D &ray);
};

#endif /* Disk_h */
