#include "Plane.h"

Plane::Plane(const Material &material, const ColourRGB &colour) :
Object3D::Object3D(material, colour) {
    Object3D::bothSidesLit = true;
}

ColourRGB Plane::colourAtLocalPoint(const Point3D &p) const {
    // If no texture, return this object's standard color
    if (textureImage == NULL) {
        return colour;
    }
    
    double a = (p.x + size/2.0) / size;
    double b = (p.y + size/2.0) / size;
    return textureImage->textureMap(a, b);
}

Intersection Plane::intersect(const Ray3D &ray) {
    Intersection intersection;
    
    /////////////////////////////////
    // TO DO: Complete this function.
    /////////////////////////////////
    
    return intersection;
}
