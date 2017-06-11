//
//  StereoCamera.h
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-11.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#ifndef StereoCamera_h
#define StereoCamera_h

#include <stdio.h>
#include "Camera.h"

class StereoCamera {
    Camera left;
    Camera right;
    
public:
    StereoCamera(const Point3D &pos, const Point3D &coa, const Point3D &axis, double f, double wsize);
};

#endif /* StereoCamera_h */
