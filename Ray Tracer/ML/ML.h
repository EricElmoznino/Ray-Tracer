//
//  ML.h
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-08.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#ifndef ML_h
#define ML_h


#include <stdio.h>
#include <list>
#include <tuple>

#include "../Camera.h"
#include "../ObjectTypes/ObjectSubclasses/Plane.h"
#include "../ObjectTypes/ObjectSubclasses/Disk.h"
#include "../ObjectTypes/ObjectSubclasses/Sphere.h"
#include "../ObjectTypes/ObjectSubclasses/Cylinder.h"
#include "../ObjectTypes/ObjectSubclasses/Cube.h"
#include "../ObjectTypes/ObjectSubclasses/Cone.h"
#include "../ObjectTypes/ObjectSubclasses/Paraboloid.h"
#include "../ObjectTypes/ObjectSubclasses/Torus.h"
#include "../ObjectTypes/ObjectSubclasses/TriangleMesh.h"
#include "../Lights/PointLightSource.h"
#include "../Lights/AreaLightElement.h"

int mainML();

void testScene(list<Object3D*> &objects, list<Light*> &lights);
void randomScene(list<Object3D*> &objects, list<Light*> &lights, Camera cam,
                 double maxFOV, double minDist, double range, int numObjects);

tuple<Camera, Point3D> perturbCamOrientation(Camera cam, double maxDeviation, double maxRotation);
tuple<Camera, Point3D> perturbCameraRoll(Camera cam, double maxRotation);
tuple<Camera, Point3D> perturbCameraPitch(Camera cam, double maxDeviation);
tuple<Camera, Point3D> perturbCameraYaw(Camera cam, double maxDeviation);
tuple<Camera, Point3D> perturbCameraYawPitch(Camera cam, double maxDeviation);


#endif /* ML_h */
