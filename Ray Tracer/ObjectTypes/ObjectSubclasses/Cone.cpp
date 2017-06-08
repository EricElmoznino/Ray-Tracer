//
//  Cone.cpp
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-07.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#include "Cone.h"
#include <algorithm>

using namespace std;

Cone::Cone(const Material &material, const ColourRGB &colour) :
Object3D::Object3D(material, colour) {
}

ColourRGB Cone::colourAtLocalPoint(const Point3D &p) const {
    // If no texture, return this object's standard color
    if (textureImage.rgbImageData == NULL) {
        return colour;
    }
    
    // TODO: get texture coordinates
    double a;
    double b;
    
    
    return textureImage.textureMap(a, b);
}

Intersection Cone::intersect(const Ray3D &ray) {
    Intersection intersection;
    
    // Acquire ray in local coordinates
    Point3D rayOrigin = invTransform*ray.origin;
    Point3D rayDirection = invTransform*ray.direction;
    
    // Compute intersection with infinite cone
    double a = rayDirection.x*rayDirection.x + rayDirection.y*rayDirection.y - rayDirection.z*rayDirection.z;
    double b = 2 * (rayDirection.x*rayOrigin.x + rayDirection.y*rayOrigin.y - rayDirection.z*rayOrigin.z);
    double c = rayOrigin.x*rayOrigin.x + rayOrigin.y*rayOrigin.y - rayOrigin.z*rayOrigin.z;
    double det = b*b - 4*a*c;
    if (det < 0) {
        intersection.none = true;
        return intersection;
    }
    double t1 = (-b + sqrt(det)) / (2 * a);
    double t2 = (-b - sqrt(det)) / (2 * a);
    if (t1 > t2) swap(t1, t2);
    
    // Check if above or below the finite cone
    double z1 = rayOrigin.z + t1*rayDirection.z;
    double z2 = rayOrigin.z + t2*rayDirection.z;
    double top = 0, bot = -1;
    if (!((z1 > bot && z1 < top) || (z2 > bot && z2 < top))) {
        intersection.none = true;
        return intersection;
    }
    
    // Compute intersections with cap plane
    double tp = t1 + (t2 - t1)*(bot - z1)/(z2 - z1);
    
    // Determine net intersections with finite capped cone
    Point3D h1, h2;
    Point3D n1, n2;
    if (z1 < bot || z1 > top) {
        t1 = tp;
        h1 = rayOrigin + t1*rayDirection;
        n1 = Point3D(0, 0, -1, true);
        h2 = rayOrigin + t2*rayDirection;
        n2 = (Point3D(h2.x, h2.y, 0, true).normalized() + Point3D(0, 0, 1, true)).normalized();
    }
    else if (z2 < bot || z2 > top) {
        t2 = tp;
        h1 = rayOrigin + t1*rayDirection;
        n1 = (Point3D(h1.x, h1.y, 0, true).normalized() + Point3D(0, 0, 1, true)).normalized();
        h2 = rayOrigin + t2*rayDirection;
        n2 = Point3D(0, 0, -1, true);
    }
    else {
        h1 = rayOrigin + t1*rayDirection;
        n1 = (Point3D(h1.x, h1.y, 0, true).normalized() + Point3D(0, 0, 1, true)).normalized();
        h2 = rayOrigin + t2*rayDirection;
        n2 = (Point3D(h2.x, h2.y, 0, true).normalized() + Point3D(0, 0, 1, true)).normalized();
    }
    if (t1 > t2) {swap(t1, t2); swap(h1, h2); swap(n1, n2);}
    
    bool insideObject, canSelfReflect;
    double lambda;
    Point3D hitPointLocal;
    Point3D hitNormalLocal;
    if (t2 < 0) {       // cone behind us
        intersection.none = true;
        return intersection;
    }
    else if (t1 <= 0) {     // inside cone
        lambda = t2;
        hitPointLocal = h2;
        hitNormalLocal = -1*n2;
        insideObject = true;
        canSelfReflect = true;
    }
    else {                  // cone in front
        lambda = t1;
        hitPointLocal = h1;
        hitNormalLocal = n1;
        insideObject = false;
        canSelfReflect = false;
    }
    
    intersection.none = false;
    intersection.insideObject = insideObject;
    intersection.lambda = lambda;
    intersection.point = ray.rayPosition(lambda);
    intersection.normal = (invTransform.transpose() * hitNormalLocal).normalized();
    intersection.material = material;
    intersection.colour = colourAtLocalPoint(hitPointLocal);
    intersection.canSelfReflect = canSelfReflect;
    intersection.obj = this;
    
    return intersection;
}

bool Cone::doesIntersect(const Ray3D &ray) {
    return !intersect(ray).none;
}

