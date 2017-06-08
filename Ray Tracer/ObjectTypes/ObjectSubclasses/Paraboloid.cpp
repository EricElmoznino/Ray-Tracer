//
//  Paraboloid.cpp
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-07.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#include "Paraboloid.h"
#include <algorithm>

using namespace std;

Paraboloid::Paraboloid(const Material &material, const ColourRGB &colour) :
Object3D::Object3D(material, colour) {
}

ColourRGB Paraboloid::colourAtLocalPoint(const Point3D &p) const {
    // If no texture, return this object's standard color
    if (textureImage.rgbImageData == NULL) {
        return colour;
    }
    
    // TODO: get texture coordinates
    double a;
    double b;
    
    
    return textureImage.textureMap(a, b);
}

Point3D Paraboloid::normalAtPoint(Point3D p) const {
    return Point3D(2*p.x, 2*p.y, -1, true).normalized();
}

Intersection Paraboloid::intersect(const Ray3D &ray) {
    Intersection intersection;
    
    // Acquire ray in local coordinates
    Point3D rayOrigin = invTransform*ray.origin;
    Point3D rayDirection = invTransform*ray.direction;
    
    // Compute intersection with infinite paraboloid
    double a = rayDirection.x*rayDirection.x + rayDirection.y*rayDirection.y;
    double b = 2 * (rayDirection.x*rayOrigin.x + rayDirection.y*rayOrigin.y) - rayDirection.z;
    double c = rayOrigin.x*rayOrigin.x + rayOrigin.y*rayOrigin.y - rayOrigin.z;
    double det = b*b - 4*a*c;
    if (det < 0) {
        intersection.none = true;
        return intersection;
    }
    double t1 = (-b + sqrt(det)) / (2 * a);
    double t2 = (-b - sqrt(det)) / (2 * a);
    if (t1 > t2) swap(t1, t2);
    
    // Check if above the finite paraboloid
    double z1 = rayOrigin.z + t1*rayDirection.z;
    double z2 = rayOrigin.z + t2*rayDirection.z;
    double top = 1;
    if (z1 > top && z2 > top) {
        intersection.none = true;
        return intersection;
    }
    
    // Determine net intersections with finite paraboloid
    double lambda;
    if (z1 > top)
        lambda = t2;
    else if (z2 > top)
        lambda = t1;
    else {
        if (t1 < 0) lambda = t2;
        else if (t2 < 0) lambda = t1;
        else lambda = min(t1, t2);
    }
    
    Point3D hitPointLocal;
    Point3D hitNormalLocal;
    if (lambda < 0) {       // parabolloid behind us
        intersection.none = true;
        return intersection;
    }
    else {                  // parabolloid in front
        hitPointLocal = rayOrigin + lambda*rayDirection;
        Point3D n = normalAtPoint(hitPointLocal);
        hitNormalLocal = rayDirection.dot(n) < 0 ? n : -1*n;
    }
    
    intersection.none = false;
    intersection.insideObject = false;
    intersection.lambda = lambda;
    intersection.point = ray.rayPosition(lambda);
    intersection.normal = (invTransform.transpose() * hitNormalLocal).normalized();
    intersection.material = material;
    intersection.colour = colourAtLocalPoint(hitPointLocal);
    intersection.canSelfReflect = true;
    intersection.obj = this;
    
    return intersection;
}

bool Paraboloid::doesIntersect(const Ray3D &ray) {
    return !intersect(ray).none;
}
