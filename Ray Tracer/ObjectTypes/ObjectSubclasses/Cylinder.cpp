//
//  Cylinder.cpp
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-06.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#include "Cylinder.h"

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
    double lambda1 = (-b + sqrt(det)) / (2 * a);
    double lambda2 = (-b - sqrt(det)) / (2 * a);
    if (lambda1 > lambda2) {
        double temp = lambda1;
        lambda1 = lambda2;
        lambda2 = temp;
    }
    double z1 = rayOrigin.z + lambda1*rayDirection.z;
    double z2 = rayOrigin.z + lambda2*rayDirection.z;
    
    // Compute the intersection with the 3D finite cylinder
    double top = height/2.0, bot = -height/2.0;
    if ((z1 > top && z2 > top) || (z1 < bot && z2 < bot)) {
        intersection.none = true;
        return intersection;
    }
    
    // Compute the intersection point and normal
    bool insideObject, canSelfReflect;
    double lambda;
    Point3D hitPointLocal;
    Point3D hitNormalLocal;
    if (z1 >= top && z2 <= bot) {
        lambda1 = lambda1 + (lambda2 - lambda1) * (top - z1)/(z2 - z1);
        lambda2 = lambda1 + (lambda2 - lambda1) * (bot - z1)/(z2 - z1);
        if (lambda2 < 0) {   // cylinder behind us
            intersection.none = true;
            return intersection;
        }
        else if (lambda1 <= 0) {  // inside cylinder
            lambda = lambda2;
            hitPointLocal = rayOrigin + lambda*rayDirection;
            hitNormalLocal = Point3D(0, 0, 1, true);
            insideObject = true;
            canSelfReflect = true;
        }
        else {                  // cylinder in front of us
            lambda = lambda1;
            hitPointLocal = rayOrigin + lambda*rayDirection;
            hitNormalLocal = Point3D(0, 0, 1, true);
            insideObject = false;
            canSelfReflect = false;
        }
    }
    else if (z1 <= bot && z2 >= top) {
        lambda1 = lambda1 + (lambda2 - lambda1) * (bot - z1)/(z2 - z1);
        lambda2 = lambda1 + (lambda2 - lambda1) * (top - z1)/(z2 - z1);
        if (lambda2 < 0) {   // cylinder behind us
            intersection.none = true;
            return intersection;
        }
        else if (lambda1 <= 0) {  // inside cylinder
            lambda = lambda2;
            hitPointLocal = rayOrigin + lambda*rayDirection;
            hitNormalLocal = Point3D(0, 0, -1, true);
            insideObject = true;
            canSelfReflect = true;
        }
        else {                  // cylinder in front of us
            lambda = lambda1;
            hitPointLocal = rayOrigin + lambda*rayDirection;
            hitNormalLocal = Point3D(0, 0, -1, true);
            insideObject = false;
            canSelfReflect = false;
        }
    }
    else if (z1 >= top && z2 >= bot && z2 <= top) {
        lambda1 = lambda1 + (lambda2 - lambda1) * (top - z1)/(z2 - z1);
        if (lambda2 < 0) {   // cylinder behind us
            intersection.none = true;
            return intersection;
        }
        else if (lambda1 <= 0) {  // inside cylinder
            lambda = lambda2;
            hitPointLocal = rayOrigin + lambda*rayDirection;
            hitNormalLocal = centre - Point3D(hitPointLocal.x, hitPointLocal.y, 0, false);
            insideObject = true;
            canSelfReflect = true;
        }
        else {                  // cylinder in front of us
            lambda = lambda1;
            hitPointLocal = rayOrigin + lambda*rayDirection;
            hitNormalLocal = Point3D(0, 0, 1, true);
            insideObject = false;
            canSelfReflect = false;
        }

    }
    else if (z1 >= bot && z1 <= top && z2 >= top) {
        lambda2 = lambda1 + (lambda2 - lambda1) * (top - z1)/(z2 - z1);
        if (lambda2 < 0) {   // cylinder behind us
            intersection.none = true;
            return intersection;
        }
        else if (lambda1 <= 0) {  // inside cylinder
            lambda = lambda2;
            hitPointLocal = rayOrigin + lambda*rayDirection;
            hitNormalLocal = Point3D(0, 0, -1, true);
            insideObject = true;
            canSelfReflect = true;
        }
        else {                  // cylinder in front of us
            lambda = lambda1;
            hitPointLocal = rayOrigin + lambda*rayDirection;
            hitNormalLocal = Point3D(hitPointLocal.x, hitPointLocal.y, 0, false) - centre;
            insideObject = false;
            canSelfReflect = false;
        }
    }
    else if (z1 <= bot && z2 >= bot && z2 <= top) {
        lambda1 = lambda1 + (lambda2 - lambda1) * (bot - z1)/(z2 - z1);
        if (lambda2 < 0) {   // cylinder behind us
            intersection.none = true;
            return intersection;
        }
        else if (lambda1 <= 0) {  // inside cylinder
            lambda = lambda2;
            hitPointLocal = rayOrigin + lambda*rayDirection;
            hitNormalLocal = centre - Point3D(hitPointLocal.x, hitPointLocal.y, 0, false);
            insideObject = true;
            canSelfReflect = true;
        }
        else {                  // cylinder in front of us
            lambda = lambda1;
            hitPointLocal = rayOrigin + lambda*rayDirection;
            hitNormalLocal = Point3D(0, 0, -1, true);
            insideObject = false;
            canSelfReflect = false;
        }
    }
    else if (z1 >= bot && z1 <= top && z2 <= bot) {
        lambda2 = lambda1 + (lambda2 - lambda1) * (bot - z1)/(z2 - z1);
        if (lambda2 < 0) {   // cylinder behind us
            intersection.none = true;
            return intersection;
        }
        else if (lambda1 <= 0) {  // inside cylinder
            lambda = lambda2;
            hitPointLocal = rayOrigin + lambda*rayDirection;
            hitNormalLocal = Point3D(0, 0, 1, true);
            insideObject = true;
            canSelfReflect = true;
        }
        else {                  // cylinder in front of us
            lambda = lambda1;
            hitPointLocal = rayOrigin + lambda*rayDirection;
            hitNormalLocal = Point3D(hitPointLocal.x, hitPointLocal.y, 0, false) - centre;
            insideObject = false;
            canSelfReflect = false;
        }
    }
    else {  // z1 >= bot && z1 <= top && z2 >= bot && z2 <= top
        if (lambda2 < 0) {  // cylinder behind us
            intersection.none = true;
            return intersection;
        }
        else if (lambda1 <= 0) {    // inside cylinder
            lambda = lambda2;
            hitPointLocal = rayOrigin + lambda*rayDirection;
            hitNormalLocal = centre - Point3D(hitPointLocal.x, hitPointLocal.y, 0, false);
            insideObject = true;
            canSelfReflect = true;
        }
        else {                  // cylinder in front of us
            lambda = lambda1;
            hitPointLocal = rayOrigin + lambda*rayDirection;
            hitNormalLocal = Point3D(hitPointLocal.x, hitPointLocal.y, 0, false) - centre;
            insideObject = false;
            canSelfReflect = false;
        }
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
