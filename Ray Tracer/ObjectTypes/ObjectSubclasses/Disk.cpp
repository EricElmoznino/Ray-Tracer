//
//  Disk.cpp
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-08.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#include "Disk.h"

Disk::Disk(const Material &material, const ColourRGB &colour) :
Object3D::Object3D(material, colour) {
}

ColourRGB Disk::colourAtLocalPoint(const Point3D &p) const {
    // If no texture, return this object's standard color
    if (textureImage.rgbImageData == NULL) {
        return colour;
    }
    
    double a = p.x + radius/2;
    double b = p.y + radius/2;
    return textureImage.textureMap(a, b);
}

Intersection Disk::intersect(const Ray3D &ray) {
    Intersection intersection;
    
    // Acquire ray in local coordinates
    Point3D rayOrigin = invTransform*ray.origin;
    Point3D rayDirection = invTransform*ray.direction;
    
    double denom = normal.dot(rayDirection);
    // Invalid intersection - disk is parallel to ray
    if (fabs(denom) < 1e-6) {
        intersection.none = true;
        return intersection;
    }
    
    double t = normal.dot(c - rayOrigin) / denom;
    // Invalid intersection - behind camera
    if (t < 0)
    {
        intersection.none = true;
        return intersection;
    }
    
    //Intersection point
    Point3D p = rayOrigin + t*rayDirection;
    
    //Check if intersects within disk's bounds
    if (p.x*p.x + p.y*p.y <= radius*radius)
    {
        Point3D hitNormalLocal = rayDirection.dot(normal) < 0 ? normal : -1*normal;
        
        intersection.none = false;
        intersection.insideObject = false;
        intersection.lambda = t;
        intersection.point = ray.rayPosition(t);
        intersection.normal = (invTransform.transpose() * hitNormalLocal).normalized();
        intersection.material = material;
        intersection.colour = colourAtLocalPoint(p);
        intersection.canSelfReflect = false;
        intersection.obj = this;
        
        return intersection;
    }
    intersection.none = true;
    return intersection;
}

bool Disk::doesIntersect(const Ray3D &ray) {
    return !intersect(ray).none;
}

