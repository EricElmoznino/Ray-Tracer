//
//  Cube.cpp
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-07.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#include "Cube.h"
#include <algorithm>

using namespace std;

Cube::Cube(const Material &material, const ColourRGB &colour) :
Object3D::Object3D(material, colour) {
}

ColourRGB Cube::colourAtLocalPoint(const Point3D &p) const {
    // If no texture, return this object's standard color
    if (textureImage.rgbImageData == NULL) {
        return colour;
    }
    
    // TODO: get texture coordinates
    double a;
    double b;
    
    
    return textureImage.textureMap(a, b);
}

Intersection Cube::intersect(const Ray3D &ray) {
    Intersection intersection;
    
    // Acquire ray in local coordinates
    Point3D rayOrigin = invTransform*ray.origin;
    Point3D rayDirection = invTransform*ray.direction;
    
    double tmin = -DBL_MAX, tmax = DBL_MAX;
    Point3D nmin, nmax;
    
    if (rayDirection.x != 0) {
        double tx1 = (-0.5 - rayOrigin.x) / rayDirection.x;
        double tx2 = (0.5 - rayOrigin.x) / rayDirection.x;
        Point3D n1 = Point3D(-1, 0, 0, true);
        Point3D n2 = Point3D(1, 0, 0, true);
        if (tx1 > tx2) {swap(tx1, tx2); swap(n1, n2);}
        if (tmin < tx1) {tmin = tx1; nmin = n1;}
        if (tmax > tx2) {tmax = tx2; nmax = n2;}
    }
    if (rayDirection.y != 0) {
        double ty1 = (-0.5 - rayOrigin.y) / rayDirection.y;
        double ty2 = (0.5 - rayOrigin.y) / rayDirection.y;
        Point3D n1 = Point3D(0, -1, 0, true);
        Point3D n2 = Point3D(0, 1, 0, true);
        if (ty1 > ty2) {swap(ty1, ty2); swap(n1, n2);}
        if ((tmin > ty2) || (tmax < ty1)) {
            intersection.none = true;
            return intersection;
        }
        if (tmin < ty1) {tmin = ty1; nmin = n1;}
        if (tmax > ty2) {tmax = ty2; nmax = n2;}
    }
    if (rayDirection.z != 0) {
        double tz1 = (-0.5 - rayOrigin.z) / rayDirection.z;
        double tz2 = (0.5 - rayOrigin.z) / rayDirection.z;
        Point3D n1 = Point3D(0, 0, -1, true);
        Point3D n2 = Point3D(0, 0, 1, true);
        if (tz1 > tz2) {swap(tz1, tz2); swap(n1, n2);}
        if ((tmin > tz2) || (tmax < tz1)) {
            intersection.none = true;
            return intersection;
        }
        if (tmin < tz1) {tmin = tz1; nmin = n1;}
        if (tmax > tz2) {tmax = tz2; nmax = n2;}
    }
    
    bool insideObject, canSelfReflect;
    double lambda;
    Point3D hitPointLocal;
    Point3D hitNormalLocal;
    if (tmax < 0) {         // box is behind
        intersection.none = true;
        return intersection;
    }
    else if (tmin <= 0) {   // inside box
        lambda = tmax;
        hitNormalLocal = -1*nmax;
        insideObject = true;
        canSelfReflect = true;
    }
    else {                  // box in front of us
        lambda = tmin;
        hitNormalLocal = nmin;
        insideObject = false;
        canSelfReflect = false;
    }
    hitPointLocal = rayOrigin + lambda*rayDirection;
    
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

bool Cube::doesIntersect(const Ray3D &ray) {
    return !intersect(ray).none;
}
