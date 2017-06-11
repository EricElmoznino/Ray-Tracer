//
//  mainML.cpp
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-08.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#include "ML.h"
#include <stdio.h>
#include <list>
#include "../RayTracer.h"
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

using namespace std;

void buildSceneML(list<Object3D*> &objects, list<Light*> &lights) {
    Object3D *obj = new Plane(Material(0.05, 0.65, 0.05, 0.5, 1, 1, 2, 0.3),  // original
                              ColourRGB(0.55, 0.8, 0.75));
    obj->scale(12, 12, 2);
    obj->rotateZ(PI/1.20);
    obj->rotateX(PI/2.25);
    obj->translate(0, -3, 13);
    obj->loadTexture("Textures/greyscale_natural_grunge2.ppm");
    objects.push_front(obj);
    
    obj = new Torus(Material::Mirror(),
                    ColourRGB(1.0, 0.25, 0.25));
    obj->scale(1, 1, 1);
    obj->rotateX(0*PI/4);
    obj->rotateY(4*PI/4);
    obj->translate(0, 0, 8.5);
    objects.push_front(obj);
    
    PointLightSource *light = new PointLightSource(ColourRGB(0.95, 0.95, 0.95),
                                                   Point3D(0.0, 15.5, -5.5, false));
    lights.push_front(light);
}

int mainML()
{
    int size = 1024;
    int maxDepth = 3;
    
    list<Object3D*> objs;
    list<Light*> lis;
    buildSceneML(objs, lis);
    
    double f = -3;
    double wsize = 4;
    double sep = 1;
    double conv = 1000;
    Point3D pos(0, 0, 0, false);
    Point3D axis(-1, 0, 0, true);
    Point3D up(0, 1, 0, true);
    StereoCamera cam(pos, axis, up, sep, conv, f, wsize);
    cam = cam.rotateZ(PI/8);
    
    // Render the image with ray tracing
    Image *im = new Image(size, size);
    RayTracer rayTracer;
    rayTracer.trackProgress = false;
    rayTracer.skybox = new Skybox("Skyboxes/lagoon_lf.ppm", "Skyboxes/lagoon_rt.ppm",
                                  "Skyboxes/lagoon_dn.ppm", "Skyboxes/lagoon_up.ppm",
                                  "Skyboxes/lagoon_bk.ppm", "Skyboxes/lagoon_ft.ppm");
    rayTracer.maxDepth = maxDepth;
    rayTracer.renderImage(cam.left, objs, lis, im, "left.ppm");
    rayTracer.renderImage(cam.right, objs, lis, im, "right.ppm");
    
    // Exit section. Clean up and return.
    delete im;
    while (!objs.empty()) {
        delete objs.front();
        objs.pop_front();
    }
    while (!lis.empty()) {
        delete lis.front();
        lis.pop_front();
    }
    return 0;
}


