#include <list>
#include "RayTracer.h"

ColourRGB RayTracer::shade(const ColourRGB &c, const Point3D &p, const Point3D &n,
                           const Ray3D &ray, int depth) {
    ColourRGB res(0.0, 0.0, 0.0);
    
    //////////////////////////////////////////////////////////////
    // TO DO: Implement this function. Refer to the notes for
    // details about the shading model.
    //////////////////////////////////////////////////////////////
    
    return res;
}

void RayTracer::findFirstHit(list<Object3D*> allObjs, const Ray3D &ray, const Object3D *source,
                             Object3D *obj, Point3D *p, Point3D *n, double *a, double *b) {
    /////////////////////////////////////////////////////////////
    // TO DO: Implement this function. See the notes for
    // reference of what to do in here
    /////////////////////////////////////////////////////////////
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
