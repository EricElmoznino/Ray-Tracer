//
//  Cylinder.cpp
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-06.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#include "Cylinder.h"
#include <algorithm>

using namespace std;

Cylinder::Cylinder(const Material &material, const ColourRGB &colour) :
Object3D::Object3D(material, colour) {
}

ColourRGB Cylinder::colourAtLocalPoint(const Point3D &p) const {
    // If no texture, return this object's standard color
    if (textureImage.rgbImageData == NULL) {
        return colour;
    }
    
    // TODO: get texture coordinates
    double a;
    double b;
    
    
    return textureImage.textureMap(a, b);
}

Intersection Cylinder::intersect(const Ray3D &ray) {
    Intersection intersection;
    
    // Acquire the ray in local coordinates
    Point3D rayOrigin = invTransform * ray.origin;
    Point3D rayDirection = invTransform * ray.direction;
    
    // Compute intersection with infinite cylinder
    double a = rayDirection.x*rayDirection.x + rayDirection.y*rayDirection.y;
    double b = 2 * (rayDirection.x*rayOrigin.x + rayDirection.y*rayOrigin.y);
    double c = rayOrigin.x*rayOrigin.x + rayOrigin.y*rayOrigin.y - radius*radius;
    double det = b*b - 4*a*c;
    if (det < 0) {
        intersection.none = true;
        return intersection;
    }
    double tc1 = (-b + sqrt(det)) / (2 * a);
    double tc2 = (-b - sqrt(det)) / (2 * a);
    if (tc1 > tc2) swap(tc1, tc2);
    
    // Check if above or below the cylinder
    double z1 = rayOrigin.z + tc1*rayDirection.z;
    double z2 = rayOrigin.z + tc2*rayDirection.z;
    double top = height/2.0, bot = -height/2.0;
    if ((z1 > top && z2 > top) || (z1 < bot && z2 < bot)) {
        intersection.none = true;
        return intersection;
    }

    // Compute intersections with cap planes
    double tp1 = tc1 + (tc2 - tc1)*(top - z1)/(z2 - z1);
    double tp2 = tc1 + (tc2 - tc1)*(bot - z1)/(z2 - z1);
    Point3D np1 = Point3D(0, 0, 1, true);
    Point3D np2 = Point3D(0, 0, -1, true);
    if (tp1 > tp2) {swap(tp1, tp2); swap(np1, np2);}
    
    // Find the appropriate ranges
    double t1 = tp1, t2 = tp2;
    Point3D n1 = np1, n2 = np2;
    Point3D h1, h2;
    if (tc1 > tp1) {
        t1 = tc1;
        h1 = rayOrigin + t1*rayDirection;
        n1 = Point3D(h1.x, h1.y, 0, false) - centre;
    }
    if (tc2 < tp2) {
        t2 = tc2;
        h2 = rayOrigin + t2*rayDirection;
        n2 = Point3D(h2.x, h2.y, 0, false) - centre;
    }
    
    // Compute the intersection point and normal
    bool insideObject, canSelfReflect;
    double lambda;
    Point3D hitPointLocal;
    Point3D hitNormalLocal;
    if (t2 < 0) {           // cylinder behind us
        intersection.none = true;
        return intersection;
    }
    else if (t1 <= 0) {     // inside cylinder
        lambda = t2;
        hitPointLocal = h2;
        hitNormalLocal = -1*n2;
        insideObject = true;
        canSelfReflect = true;
    }
    else {                  // outside cylinder
        lambda = t1;
        hitPointLocal = h1;
        hitNormalLocal = n1;
        insideObject = false;
        canSelfReflect = false;
    }
    
    intersection.none = false;
    intersection.insideObject = insideObject;
    intersection.lambda = lambda;
    intersection.point = ray.rayPosition(lambda);   // lambda is the same for local and world
    intersection.normal = (invTransform.transpose() * hitNormalLocal).normalized();
    intersection.material = material;
    intersection.colour = colourAtLocalPoint(hitPointLocal);
    intersection.canSelfReflect = canSelfReflect;
    intersection.obj = this;
    
    return intersection;
}

bool Cylinder::doesIntersect(const Ray3D &ray) {
    return !intersect(ray).none;
}
