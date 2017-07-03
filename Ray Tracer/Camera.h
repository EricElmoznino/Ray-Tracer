#ifndef Camera_h
#define Camera_h

#include <stdio.h>
#include "GeometricTypes/Transform3D.h"

class Camera {
public:
    double f;   // focal length
    double wsize;   // window size in distance units (not pixels!)
    
    Transform3D worldToCamera;
    Transform3D cameraToWorld;
    
    /*
     This function sets up the camera axes and viewing direction:
     e - Camera center
     g - Gaze direction
     up - Up vector
     fov - Fild of view in degrees
     f - focal length
     */
    Camera(const Point3D &e, const Point3D &g, const Point3D &up,
         double f, double wsize);
    
    Camera translate(double x, double y, double z);
    Camera orient(double yaw, double pitch, double roll);
};

#endif
