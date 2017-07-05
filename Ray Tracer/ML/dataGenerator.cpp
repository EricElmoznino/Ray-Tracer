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

Object3D *randomObject() {
    switch ((int)(drand48()*6 + 1)) {
        case 1:
            return new Cone(Material::randomMaterial(), ColourRGB::randomColour());
            break;
        case 2:
            return new Cube(Material::randomMaterial(), ColourRGB::randomColour());
            break;
        case 3:
            return new Cylinder(Material::randomMaterial(), ColourRGB::randomColour());
            break;
        case 4:
            return new Paraboloid(Material::randomMaterial(), ColourRGB::randomColour());
            break;
        case 5:
            return new Sphere(Material::randomMaterial(), ColourRGB::randomColour());
            break;
        case 6:
            return new Torus(Material::randomMaterial(), ColourRGB::randomColour());
            break;
        default:
            return new Torus(Material::randomMaterial(), ColourRGB::randomColour());
    }
}

void randomScene(list<Object3D*> &objects, list<Light*> &lights, Camera cam,
                 double maxFOV, double minDist, double range, int numObjects) {
    clearList(objects);
    clearList(lights);
    
    for (int i = 0; i < numObjects; i++) {
        Object3D *obj = randomObject();
        
        Point3D scale = Point3D(drand48()+0.2, drand48()+0.2, drand48()+0.2, true).normalized();
        obj->scale(scale.x, scale.y, scale.z);
        
        Point3D rotation = 2*PI * Point3D(drand48(), drand48(), drand48(), true);
        obj->rotateX(rotation.x);
        obj->rotateY(rotation.y);
        obj->rotateZ(rotation.z);
        
        Point3D direction = -1*Point3D::randomNormal(maxFOV/2); // camera faces in negative z
        double distance = drand48()*range + minDist;
        Point3D position = distance * (cam.getTransform() * direction);
        obj->translate(position.x, position.y, position.z);
        
        objects.push_front(obj);
    }
    
    PointLightSource *light = new PointLightSource(ColourRGB(0.95, 0.95, 0.95),
                                                   Point3D(0.0, 15.5, -5.5, false));
    lights.push_front(light);
}

tuple<Camera, Point3D> perturbCamOrientation(Camera cam, double maxDeviation, double maxRotation) {
    Point3D sample = Point3D::randomNormal(maxDeviation);
    double yaw = atan(sample.x/sample.z);
    double pitch = atan(sample.y/sample.z);
    double roll = (2*drand48() - 1) * maxRotation;
    cam = cam.orient(yaw, pitch, roll);
    Point3D perturbation(yaw, pitch, roll, true);
    return make_tuple(cam, perturbation);
}

tuple<Camera, Point3D> perturbCameraRoll(Camera cam, double maxRotation) {
    return perturbCamOrientation(cam, 0, maxRotation);
}

tuple<Camera, Point3D> perturbCameraPitch(Camera cam, double maxDeviation) {
    double pitch = (2*drand48() - 1) * maxDeviation;
    cam.orient(0, pitch, 0);
    Point3D perturbation(0, pitch, 0, true);
    return make_tuple(cam, perturbation);
}

tuple<Camera, Point3D> perturbCameraYaw(Camera cam, double maxDeviation) {
    double yaw = (2*drand48() - 1) * maxDeviation;
    cam.orient(yaw, 0, 0);
    Point3D perturbation(yaw, 0, 0, true);
    return make_tuple(cam, perturbation);
}

tuple<Camera, Point3D> perturbCameraYawPitch(Camera cam, double maxDeviation) {
    return perturbCamOrientation(cam, maxDeviation, 0);
}

