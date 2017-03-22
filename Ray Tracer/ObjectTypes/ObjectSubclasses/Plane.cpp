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
    
    // TO DO: Complete this function. Will need to find the (a,b)
    // texture coordinates at p given this type of object and then
    // call Image's textureMap function
    return ColourRGB(0, 0, 0);  // temporary until function is implemented
}

Intersection Plane::intersect(const Ray3D &ray) {
    Intersection intersection;
    
    /////////////////////////////////
    // TO DO: Complete this function.
    /////////////////////////////////
    
    return intersection;
}
