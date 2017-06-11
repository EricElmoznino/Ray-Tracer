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

#include "../StereoCamera.h"
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

#define PI 3.14159265354

int mainML();

void testScene(list<Object3D*> &objects, list<Light*> &lights);
void randomScene(list<Object3D*> &objects, list<Light*> &lights, Point3D dir, double maxFOV);

StereoCamera perturbCamOrientation(StereoCamera cam, double maxTheta);

#endif /* ML_h */
