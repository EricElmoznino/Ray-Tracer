#ifndef RayTracer_h
#define RayTracer_h

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "PointLightSource.h"
#include "View.h"

class RayTracer {
    const int superSamplingResolution = 5;
    
    list<Object3D*> objects;
    list<PointLightSource> lights;
    int maxDepth;
    
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
    // source is needed for recursive calls to ensure that findFirstHit will
    // not simply return a self-intersection due to numerical
    // errors. For the top level call, source should be NULL. And thereafter
    // it will correspond to the object from which the recursive
    // ray originates.
    ColourRGB rayTraceRecursive(const Ray3D &ray, int depth, const Object3D *source);
    
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
    Intersection findFirstHit(const Ray3D &ray, const Object3D *source);
    
    ColourRGB phongModel(const Intersection &intersection, const Ray3D &ray);
    
    bool isInShadow(const Intersection &intersection, const PointLightSource &light);
    
    ColourRGB reflection(const Intersection &intersection, const Ray3D &ray, int depth);
    
public:
    bool antialiasingEnabled = false;
	bool glossyreflEnabled = false;
    
    void renderImage(View camera, list<Object3D*> objects, list<PointLightSource> lights,
                     int maxDepth, Image *output, char * name);
};

#endif
