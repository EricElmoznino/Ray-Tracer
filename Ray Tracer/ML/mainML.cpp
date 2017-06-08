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
    obj->translate(0, -3, 10);
    obj->loadTexture("Textures/greyscale_natural_grunge2.ppm");
    objects.push_front(obj);
    
    obj = new Paraboloid(Material::Mirror(),
                    ColourRGB(1.0, 0.25, 0.25));
    obj->scale(1, 1, 1);
    obj->rotateX(0*PI/4);
    obj->rotateY(4*PI/4);
    obj->translate(0, 0, 5.5);
    objects.push_front(obj);
    
    PointLightSource *light = new PointLightSource(ColourRGB(0.95, 0.95, 0.95),
                                                   Point3D(0.0, 15.5, -5.5, false));
    lights.push_front(light);
}

int mainML()
{
    int size = 1024;
    int maxDepth = 3;
    
    Image *im;
    char output_name[1024] = "RenderedImage.ppm";
    Point3D e;
    Point3D g;
    Point3D up;
    ColourRGB background(0.0, 0.0, 0.0);
    RayTracer rayTracer;
    
    
    // Allocate memory for the new image
    im = new Image(size, size);
    
    list<Object3D*> objs;
    list<Light*> lis;
    buildSceneML(objs, lis);
    
    // Camera center is at (0,0,-3)
    e = Point3D(0.0, 0.0, -3.0, false);
    
    // To define the gaze vector, we choose a point 'pc' in the scene that
    // the camera is looking at, and do the vector subtraction pc-e.
    // Here we set up the camera to be looking at the origin
    g = Point3D(0.0, 0.0, 0.0, false) - e;
    
    // Define the 'up' vector to be the Y axis
    up = Point3D(0, 1, 0, true);
    
    // Set up view with given the above vectors, a 4x4 window,
    // and a focal length of -1 (why? where is the image plane?)
    // Note that the top-left corner of the window is at (2, 2)
    // in camera coordinates.
    Camera cam(e, g, up, -3, 4);
    
    fprintf(stderr,"View parameters:\n");
    fprintf(stderr,"Width=%f, f=%f\n", cam.wsize,cam.f);
    fprintf(stderr,"Camera to world conversion matrix (make sure it makes sense!):\n");
    cam.cameraToWorld.printTransform3D();
    fprintf(stderr,"World to camera conversion matrix\n");
    cam.worldToCamera.printTransform3D();
    fprintf(stderr,"\n");
    
    // Render the image with ray tracing
    rayTracer.skybox = new Skybox("Skyboxes/lagoon_lf.ppm", "Skyboxes/lagoon_rt.ppm",
                                  "Skyboxes/lagoon_dn.ppm", "Skyboxes/lagoon_up.ppm",
                                  "Skyboxes/lagoon_bk.ppm", "Skyboxes/lagoon_ft.ppm");
    rayTracer.maxDepth = maxDepth;
    rayTracer.renderImage(cam, objs, lis, im, output_name);
    
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


