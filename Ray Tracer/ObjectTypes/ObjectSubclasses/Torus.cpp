//
//  Torus.cpp
//  Ray Tracer
//
//  Created by Eric Elmoznino on 2017-06-08.
//  Copyright © 2017 Eric Elmoznino. All rights reserved.
//

#include "Torus.h"
#include <algorithm>
#include "../../Utilities/poly34.h"

using namespace std;

Torus::Torus(const Material &material, const ColourRGB &colour) :
Object3D::Object3D(material, colour) {
}

ColourRGB Torus::colourAtLocalPoint(const Point3D &p) const {
    // If no texture, return this object's standard color
    if (textureImage.rgbImageData == NULL) {
        return colour;
    }
    
    // TODO: get texture coordinates
    double a;
    double b;
    
    
    return textureImage.textureMap(a, b);
}

Point3D Torus::normalAtPoint(Point3D p) const {
    double a = 1 - R/sqrt(p.x*p.x + p.y*p.y);
    return Point3D(2*p.x*a, 2*p.y*a, 2*p.z, true).normalized();
}

Intersection Torus::intersect(const Ray3D &ray) {
    Intersection intersection;
    
    // Acquire ray in local coordinates
    Point3D o = invTransform*ray.origin;
    Point3D d = invTransform*ray.direction;
    
    // Compute intersection with infinite cone
    double a = pow(d.x, 4)+pow(d.y, 4)+pow(d.z, 4) + 2*(d.x*d.x*d.y*d.y+d.x*d.x*d.z*d.z+d.y*d.y*d.z*d.z);
    double b = 4*(pow(d.x, 3)*o.x+pow(d.y, 3)*o.y+pow(d.z, 3)*o.z+d.x*d.x*d.y*o.y+d.x*d.x*d.z*o.z+d.x*o.x*d.y*d.y+d.y*d.y*d.z*o.z+d.x*o.x*d.z*d.z+d.y*o.y*d.z*d.z);
    double c = 2*(-R*R*d.x*d.x-R*R*d.y*d.y+R*R*d.z*d.z-r*r*d.x*d.x-r*r*d.y*d.y-r*r*d.z*d.z+3*d.x*d.x*o.x*o.x+o.x*o.x*d.y*d.y+4*d.x*o.x*d.y*o.y+d.x*d.x*o.y*o.y+3*d.y*d.y*o.y*o.y+o.x*o.x*d.z*d.z+o.y*o.y*d.z*d.z+4*d.x*o.x*d.z*o.z+4*d.y*o.y*d.z*o.z+d.x*d.x*o.z*o.z+d.y*d.y*o.z*o.z+3*d.z*d.z*o.z*o.z);
    double dp = 4*(-R*R*d.x*o.x-R*R*d.y*o.y+R*R*d.z*o.z-r*r*d.x*o.x-r*r*d.y*o.y-r*r*d.z*o.z+d.x*pow(o.x, 3)+o.x*o.x*d.y*o.y+d.x*o.x*o.y*o.y+d.y*pow(o.y, 3)+o.x*o.x*d.z*o.z+o.y*o.y*d.z*o.z+d.x*o.x*o.z*o.z+d.y*o.y*o.z*o.z+d.z*pow(o.z, 3));
    double e = pow(R, 4)+pow(r, 4)+pow(o.x, 4)+pow(o.y, 4)+pow(o.z, 4) + 2*(-R*R*o.x*o.x-R*R*o.y*o.y+R*R*o.z*o.z-R*R*r*r-r*r*o.x*o.x-r*r*o.y*o.y-r*r*o.z*o.z+o.x*o.x*o.y*o.y+o.x*o.x*o.z*o.z+o.y*o.y*o.z*o.z);
    
    double res[4];
    vector<double> back;
    vector<double> front;
    int nSolutions = SolveP4(res, b/a, c/a, dp/a, e/a);
    if (nSolutions == 0) {
        intersection.none = true;
        return intersection;
    }
    for (int i = 0; i < nSolutions; i++)
        res[i] < 0 ? back.push_back(res[i]) : front.push_back(res[i]);
    sort(back.begin(), back.end());
    sort(front.begin(), front.end());
    
    bool insideObject;
    if (front.empty()) {
        intersection.none = true;
        return intersection;
    }
    else if (front.size() == 1 && front.size() == 3)
        insideObject = true;
    else
        insideObject = false;
    
    double lambda = front[0];
    Point3D hitPointLocal = o + lambda*d;
    Point3D hitNormalLocal = normalAtPoint(hitPointLocal);
    
    intersection.none = false;
    intersection.insideObject = insideObject;
    intersection.lambda = lambda;
    intersection.point = ray.rayPosition(lambda);
    intersection.normal = (invTransform.transpose() * hitNormalLocal).normalized();
    intersection.material = material;
    intersection.colour = colourAtLocalPoint(hitPointLocal);
    intersection.canSelfReflect = true;
    intersection.obj = this;
    
    return intersection;
}

bool Torus::doesIntersect(const Ray3D &ray) {
    return !intersect(ray).none;
}


