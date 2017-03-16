#include <list>
#include "RayTracer.h"

ColourRGB RayTracer::shade(const Intersection &intersection, const Ray3D &ray, int depth) {
    ColourRGB res(0.0, 0.0, 0.0);
    
    //////////////////////////////////////////////////////////////
    // TO DO: Implement this function. Refer to the notes for
    // details about the shading model.
    //////////////////////////////////////////////////////////////
    
    return res;
}

ColourRGB RayTracer::rayTraceRecursive(const Ray3D &ray, int depth, const Object3D *source) {
    ///////////////////////////////////////////////////////
    // TO DO: Complete this function. Refer to the notes
    // if you are unsure what to do here.
    ///////////////////////////////////////////////////////
    
    // End the recursive calls and return a black colour
    // that will have no contribution
    if (depth <= 0) {
        return ColourRGB(0, 0, 0);
    }
    
    Intersection firstHit = findFirstHit(ray, source);
    return shade(firstHit, ray, depth);
}

Intersection RayTracer::findFirstHit(const Ray3D &ray, const Object3D *source) {
    Intersection intersection;
    
    /////////////////////////////////////////////////////////////
    // TO DO: Implement this function. See the notes for
    // reference of what to do in here
    /////////////////////////////////////////////////////////////
    
    return intersection;
}

ColourRGB RayTracer::rayTrace(const Ray3D &ray) {
    return rayTraceRecursive(ray, maxDepth, NULL);
}
