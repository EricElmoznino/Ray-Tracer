#ifndef RayTracer_h
#define RayTracer_h

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "ObjectTypes/PointLightSource.h"

class RayTracer {
    // This function implements the shading model as described in lecture. It takes
    // - A list of objects
    // - The first object intersected by the ray (to get the colour properties)
    // - The coordinates of the intersection point (in world coordinates)
    // - The normal at the point
    // - The ray (needed to determine the reflection direction to use for the global component, as well as for
    //   the Phong specular component)
    // - The current racursion depth
    // - The (a,b) texture coordinates (meaningless unless texture is enabled)
    //
    // Returns:
    // - The colour for this ray (using the col pointer)
    //
    ColourRGB shade(list<Object3D*> allObjs, const Object3D &obj, const Point3D &p, const Point3D &n,
                    const Ray3D &ray, int depth, double a, double b);
    
    // Find the closest intersection between the ray and any objects in the scene.
    // It returns:
    //   - The lambda at the intersection (or < 0 if no intersection)
    //   - The object at the intersection (so we can evaluate the colour in the shading function)
    //   - The location of the intersection point (in p)
    //   - The normal at the intersection point (in n)
    //   - The (a,b) texture coordinates (meaningless unless texture is enabled)
    //
    // source is the 'source' object for the ray we are processing, can be NULL,
    // and is used to ensure we don't
    // return a self-intersection due to numerical errors for recursive raytrace calls.
    //
    void findFirstHit(list<Object3D*> allObjs, const Ray3D &ray, const Object3D *source,
                      Object3D *obj, Point3D *p, Point3D *n, double *a, double *b);
    
public:
    // Ray-Tracing function. It finds the closest intersection between
    // the ray and any scene objects, calls the shading function to
    // determine the colour at this intersection, and returns the
    // colour.
    //
    // source is needed for recursive calls to ensure that findFirstHit will
    // not simply return a self-intersection due to numerical
    // errors. For the top level call, source should be NULL. And thereafter
    // it will correspond to the object from which the recursive
    // ray originates.
    //
    ColourRGB rayTrace(list<Object3D*> allObjs, const Ray3D &ray,
                       int depth, const Object3D *source, int maxDepth);
};

#endif
