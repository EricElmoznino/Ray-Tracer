//
//  StereoCamera.cpp
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-11.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#include "StereoCamera.h"

StereoCamera::StereoCamera(const Point3D &pos, const Point3D &coa, const Point3D &axis, double f, double wsize) :
left(Point3D(0, 0, 0, false), Point3D(0, 0, 0, true), Point3D(0, 0, 0, true), 0, 0),
right(Point3D(0, 0, 0, false), Point3D(0, 0, 0, true), Point3D(0, 0, 0, true), 0, 0){
    
}
