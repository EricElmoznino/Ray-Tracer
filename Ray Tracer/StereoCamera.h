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
    Point3D pos;
    Point3D axis;
    Point3D up;
    
    double sep;
    double conv;
    double f;
    double wsize;
    
public:
    Camera left;
    Camera right;
    
    StereoCamera(const Point3D &pos, const Point3D &axis, const Point3D &up, double sep, double conv, double f, double wsize);
    
    StereoCamera translate(double x, double y, double z);
    StereoCamera orient(double yaw, double pitch, double roll);
};

#endif /* StereoCamera_h */
