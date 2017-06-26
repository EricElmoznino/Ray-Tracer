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

int mainML()
{
    int samples = 200;
    int size = 100;
    int maxDepth = 1;

    srand48(time(0));
    
    list<Object3D*> objs;
    list<Light*> lis;
    
    double f = -3;
    double wsize = 4;
    double sep = 1;
    double conv = 1000;
    Point3D pos(0, 0, 0, false);
    Point3D axis(-1, 0, 0, true);
    Point3D up(0, 1, 0, true);
    StereoCamera camRef(pos, axis, up, sep, conv, f, wsize);
    
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
        string s = "/Users/Eric/Desktop/validation_data/" + to_string(i) + "_";
        //randomScene(objs, lis, Point3D(0, 0, 1, true), PI/4);
        
        string s_ref = s + "ref_";
        rayTracer.renderImage(camRef.left, objs, lis, im, (s_ref+"l.ppm").c_str());
        rayTracer.renderImage(camRef.right, objs, lis, im, (s_ref+"r.ppm").c_str());
        
        string s_new = s + "new_";
        tuple<StereoCamera, Point3D> perturb = perturbCamOrientation(camRef, PI/4);
        StereoCamera camNew = get<0>(perturb);
        Point3D orientation = get<1>(perturb);
        orientation = (180.0/PI)*orientation;
        s_new += to_string(orientation.x) + "x" + to_string(orientation.y) + "x" + to_string(orientation.z) + "_";
        rayTracer.renderImage(camNew.left, objs, lis, im, (s_new+"l.ppm").c_str());
        rayTracer.renderImage(camNew.right, objs, lis, im, (s_new+"r.ppm").c_str());

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
    return 0;
}


