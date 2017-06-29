//
//  StereoCamera.cpp
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-11.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#include "StereoCamera.h"

StereoCamera::StereoCamera(const Point3D &pos, const Point3D &axis, const Point3D &up, double sep, double conv, double f, double wsize) :
left(Point3D(0, 0, 0, false), Point3D(0, 0, 0, true), Point3D(0, 0, 0, true), 0, 0),
right(Point3D(0, 0, 0, false), Point3D(0, 0, 0, true), Point3D(0, 0, 0, true), 0, 0){
    this->pos = pos;
    this->axis = axis;
    this->up = up;
    this->sep = sep;
    this->conv = conv;
    this->f = f;
    this->wsize = wsize;
    
    Point3D direction = up.crossUnit(axis);
    
    Point3D delta = -0.5*sep*axis.normalized();
    Point3D camPos = pos.shift(delta);
    Point3D gaze = pos.shift(conv*direction) - camPos;
    left = Camera(camPos, gaze, up, f, wsize);
    
    delta = 0.5*sep*axis.normalized();
    camPos = pos.shift(delta);
    gaze = pos.shift(conv*direction) - camPos;
    right = Camera(camPos, gaze, up, f, wsize);
}

StereoCamera StereoCamera::translate(double x, double y, double z) {
    return StereoCamera(pos.shift(Point3D(x, y, z, true)), axis, up, sep, conv, f, wsize);
}

StereoCamera StereoCamera::orient(double yaw, double pitch, double roll) {
    Transform3D curCamToWorld = Transform3D(-1*axis.normalized(), up.normalized(), up.crossUnit(axis), pos);
    Transform3D newCamToWorld = Transform3D::rotatedZ(roll)*Transform3D::rotatedX(pitch)*Transform3D::rotatedY(yaw)*curCamToWorld;
    return StereoCamera(pos, newCamToWorld*Point3D(-1, 0, 0, true), newCamToWorld*Point3D(0, 1, 0, true), sep, conv, f, wsize);
}
