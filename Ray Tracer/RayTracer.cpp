#include <list>
#include "RayTracer.h"

ColourRGB RayTracer::shade(Intersection intersection, const Ray3D &ray, int depth) {
    ColourRGB res(0.0, 0.0, 0.0);
    
    //////////////////////////////////////////////////////////////
    // TO DO: Implement this function. Refer to the notes for
    // details about the shading model.
    //////////////////////////////////////////////////////////////
    
    return res;
}

Intersection RayTracer::findFirstHit(list<Object3D*> allObjs, const Ray3D &ray, const Object3D *source) {
    Intersection intersection;
    
    /////////////////////////////////////////////////////////////
    // TO DO: Implement this function. See the notes for
    // reference of what to do in here
    /////////////////////////////////////////////////////////////
    
    return intersection;
}

ColourRGB RayTracer::rayTrace(list<Object3D*> allObjs, const Ray3D &ray,
                              int depth, const Object3D *source, int maxDepth) {
    ColourRGB res(0.0, 0.0, 0.0);
    
    double lambda;  // Lambda at intersection
    double a,b;		// Texture coordinates
    Object3D *obj;	// Pointer to object at intersection
    Point3D *p;     // Intersection point
    Point3D *n;	// Normal at intersection
    
    if (depth > maxDepth) {
        return ColourRGB(-1, -1, -1);
    }
    
    ///////////////////////////////////////////////////////
    // TO DO: Complete this function. Refer to the notes
    // if you are unsure what to do here.
    ///////////////////////////////////////////////////////
    
    return res;
}
