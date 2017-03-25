#include "Plane.h"

Plane::Plane(const Material &material, const ColourRGB &colour) :
Object3D::Object3D(material, colour) {
    Object3D::bothSidesLit = true;
    Object3D::isLight = false;
}

ColourRGB Plane::colourAtLocalPoint(const Point3D &p) const {
    // If no texture, return this object's standard color
    if (textureImage.rgbImageData == NULL) {
        return colour;
    }
    
    double a = (p.x - p3.x) / (p1.x - p3.x);
    double b = (p.y - p3.y) / (p1.y - p3.y);
    return textureImage.textureMap(a, b);
}

Intersection Plane::intersect(const Ray3D &ray) {
    Intersection intersection;
    
    /////////////////////////////////
    // TO DO: Complete this function.
    /////////////////////////////////
    
    // Acquire ray in local coordinates
    Point3D rayOrigin = invTransform*ray.origin; //e
    Point3D rayDirection = invTransform*ray.direction; //d
    
    //For triangle p2, p3, p4 in plane
    Point3D ab = p3 - p2;
    Point3D ac = p3 - p4;
    Point3D ae = p3 - rayOrigin;
    Point3D h(0.0, 0.0, 0.0, false);
    
    Transform3D A(ab, ac, rayDirection, h);
    A = A.inverse();
    
    //a.x = beta1, a.y = gamma1, a.z = t1 (a solution!)
    Point3D a = A*(ae);
    
    //For triangle p4, p1, p2 in the plane
    Point3D db = p1 - p2;
    Point3D dc = p1 - p4;
    Point3D de = p1 - rayOrigin;
    
    Transform3D B(db, dc, rayDirection, h);
    B = B.inverse();
    
    //b.x = beta2, b.y = gamma2, b.z = t2 (a solution!)
    Point3D b = B*(de);
    
    // If either lambda is negative, the plane is behind us (or we are in it)
    // and we don't want to render it. The case where we are in it might be
    // debatable as to whether or not we want to render, but if we change our
    // mind latter it's an easy fix.
    if (a.z < 0.0 || b.z < 0.0)
    {
        intersection.none = true;
        return intersection;
    }
    
    //Verify if the solution is inside the respective triangle
    bool inA = (a.x > 0.0 && a.y > 0.0 && a.x + a.y < 1.0);
    bool inB = (b.x > 0.0 && b.y > 0.0 && b.x + b.y < 1.0);
    
    double lambda;
    //If there is an intersection point in both triangles, take closest
    if (inA && inB){
        lambda = a.z < b.z ? a.z : b.z;
    }
    else if (inA)
    {
        lambda = a.z;
    }
    else if (inB)
    {
        lambda = b.z;
    }
    else{
        intersection.none = true;
        return intersection;
    }
    
    Point3D hitPointLocal = rayOrigin + lambda*rayDirection;
    Point3D hitNormalLocal = rayDirection.dot(normal) < 0 ? normal : -1*normal;
    
    intersection.none = false;
    intersection.isLight = Object3D::isLight;
    intersection.lambda = lambda;
    intersection.point = ray.rayPosition(lambda);
    intersection.normal = (invTransform.transpose() * hitNormalLocal).normalized();
    intersection.material = material;
    intersection.colour = colourAtLocalPoint(hitPointLocal);
    intersection.obj = this;
    
    return intersection;
}
