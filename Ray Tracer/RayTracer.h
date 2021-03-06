#ifndef RayTracer_h
#define RayTracer_h

#include<stdio.h>
#include<stdlib.h>
#include <list>
#include<math.h>
#include<string.h>
#include "Lights/Light.h"
#include "ObjectTypes/Object3D.h"
#include "ObjectTypes/Intersection.h"
#include "ObjectTypes/Ray3D.h"
#include "Camera.h"
#include "Skybox.h"

using namespace std;

// TODO: Depth of field, spotlight, combine reflection+refraction into 1 model with fresnel, better scene

class RayTracer {
    
    list<Object3D*> objects;
    list<Light*> lights;
    
    // Ray-Tracing function. It finds the closest intersection between
    // the ray and any scene objects, calls the shading function to
    // determine the colour at this intersection, and returns the
    // colour.
    //
    // Since Ray-Tracing is recursive, this is the entry point that simply
    // calls the recursive version with the appropriate starting parameters.
    //
    // pixelSize is used if antialiasing is enabled
    ColourRGB rayTrace(Ray3D ray, double pixelSize);
    
    // Recursive version of rayTrace. rayTrace is basically the public interface
    // that delegates to this function with the correct parameters
    //
    // excludedSource is needed for recursive calls when computing reflection,
    // since to save computation time we assume that object's can't reflect onto themselves
    ColourRGB rayTraceRecursive(const Ray3D &ray, int depth, Object3D *excludedSource = NULL);
    
    // This function implements the shading model as described in lecture. It takes
    // - An intersection data model that contains all necessary information for shading
    // - The ray (needed to determine the reflection direction to use for the global component, as well as for
    //   the Phong specular component)
    // - The current recursion depth
    //
    // Returns:
    // - The colour for this ray
    //
    ColourRGB shade(const Intersection &intersection, const Ray3D &ray, int depth);
    
    
    // Find the closest intersection between the ray and any objects in the scene.
    // It returns:
    //   - An intersection data model that contains all necessary information for shading
    //
    // source is the 'source' object for the ray we are processing, can be NULL,
    // and is used to ensure we don't
    // return a self-intersection due to numerical errors for recursive raytrace calls.
    //
    Intersection findFirstHit(const Ray3D &ray, Object3D *excludedSource);
    
    ColourRGB phongModel(const Intersection &intersection, const Ray3D &ray);
    
    bool isInShadow(const Intersection &intersection, const Point3D &lightLocation);
    
    ColourRGB reflection(const Intersection &intersection, const Ray3D &ray, int depth);
    
    ColourRGB refraction(const Intersection &intersection, const Ray3D &ray, int depth);
    
public:
    bool trackProgress = true;
    bool antialiasingEnabled = false;
    bool glossyreflEnabled = false;
    bool blurEnabled = false;
    bool refractionEnabled = false;
    int maxDepth = 3;
    int superSamplingResolution = 5;
    int glossyResolution = 8;
    int blurResolution = 8;
    Skybox *skybox = NULL;
    
    void renderImage(Camera camera, list<Object3D*> objects, list<Light*> lights,
                     Image *output, const char * name, vector<int> bounds = vector<int>());
};

#endif
