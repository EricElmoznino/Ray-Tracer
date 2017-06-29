//
//  dataGenerator.cpp
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-11.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#include "ML.h"

template <typename T>
void clearList(list<T*> &l) {
    while (!l.empty()) {
        delete l.front();
        l.pop_front();
    }
}

void testScene(list<Object3D*> &objects, list<Light*> &lights) {
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

void randomScene(list<Object3D*> &objects, list<Light*> &lights, Point3D dir, double maxFOV) {
    clearList(objects);
    clearList(lights);
    
    return testScene(objects, lights);
}

tuple<StereoCamera, Point3D> perturbCamOrientation(StereoCamera cam, double maxDeviation, double maxRotation) {
    Point3D sample = Point3D::randomNormal(maxDeviation);
    double yaw = atan(sample.x/sample.z);
    double pitch = atan(sample.y/sample.z);
    double roll = (2*drand48() - 1) * maxRotation;
    cam = cam.orient(yaw, pitch, roll);
    Point3D perturbation(yaw, pitch, roll, true);
    return make_tuple(cam, perturbation);
}
