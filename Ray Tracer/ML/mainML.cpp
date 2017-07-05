//
//  mainML.cpp
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-08.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#include "ML.h"
#include "../RayTracer.h"

using namespace std;

void phase1(int samples, int size, int maxDepth) {
    list<Object3D*> objs;
    list<Light*> lis;
    
    double f = -3;
    double wsize = 4;
    Point3D pos(0, 0, 0, false);
    Point3D gaze(0, 0, 1, true);
    Point3D up(0, 1, 0, true);
    Camera camRef(pos, gaze, up, f, wsize);
    
    Image *im = new Image(size, size);
    Skybox *skybox = NULL;
    skybox = new Skybox("Skyboxes/lagoon_lf.ppm", "Skyboxes/lagoon_rt.ppm",
                        "Skyboxes/lagoon_dn.ppm", "Skyboxes/lagoon_up.ppm",
                        "Skyboxes/lagoon_bk.ppm", "Skyboxes/lagoon_ft.ppm");
    RayTracer rayTracer;
    rayTracer.skybox = skybox;
    rayTracer.trackProgress = false;
    rayTracer.maxDepth = maxDepth;

    
    for (int i = 0; i < samples; i++) {
        string s = "/Users/Eric/ML_data/Attitude_1/data_yawpitch/prediction_data/" + to_string(i) + "_";
        
        string s_ref = s + "ref_";
        rayTracer.renderImage(camRef, objs, lis, im, (s_ref+".ppm").c_str());
        
        string s_new = s + "new_";
        tuple<Camera, Point3D> perturb = perturbCamOrientation(camRef, PI/4, PI/4);
        Camera camNew = get<0>(perturb);
        Point3D orientation = get<1>(perturb);
        orientation = (180.0/PI)*orientation;
        s_new += to_string(orientation.x) + "x" + to_string(orientation.y) + "x" + to_string(orientation.z) + "_";
        rayTracer.renderImage(camNew, objs, lis, im, (s_new+".ppm").c_str());
        
        printf("%d / %d\n", i+1, samples);
    }
    
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
}

void phase2(int samples, int size, int maxDepth) {
    list<Object3D*> objs;
    list<Light*> lis;
    
    double f = -3;
    double wsize = 4;
    Point3D pos(0, 0, 0, false);
    Point3D gaze(0, 0, 1, true);
    Point3D up(0, 1, 0, true);
    Camera camRef(pos, gaze, up, f, wsize);
    
    Image *im = new Image(size, size);
    Skybox *skybox = NULL;
    RayTracer rayTracer;
    rayTracer.antialiasingEnabled = true;
    rayTracer.skybox = skybox;
    rayTracer.trackProgress = false;
    rayTracer.maxDepth = maxDepth;

    for (int i = 0; i < samples; i++) {
        string s = "/Users/Eric/ML_data/Attitude_2/train_data/" + to_string(i) + "_";
        randomScene(objs, lis, camRef, PI/2, 2, 3, 6);
        
        string s_ref = s + "ref_";
        rayTracer.renderImage(camRef, objs, lis, im, (s_ref+".ppm").c_str());
        
        string s_new = s + "new_";
        tuple<Camera, Point3D> perturb = perturbCamOrientation(camRef, PI/14, PI/14);
        Camera camNew = get<0>(perturb);
        Point3D orientation = get<1>(perturb);
        orientation = (180.0/PI)*orientation;
        s_new += to_string(orientation.x) + "x" + to_string(orientation.y) + "x" + to_string(orientation.z) + "_";
        rayTracer.renderImage(camNew, objs, lis, im, (s_new+".ppm").c_str());
        
        printf("%d / %d\n", i+1, samples);
    }
    
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
}

int mainML()
{
    int samples = 10000;
    int size = 80;
    int maxDepth = 0;

    srand48(time(0));
    
    
//    phase1(samples, size, maxDepth);
    phase2(samples, size, maxDepth);
    
    
    return 0;
}


