#include "Plane.h"

Plane::Plane(const AlbedosPhong &albedos, const ColourRGB &colour,
             double alpha, double refractionIndex, double shinyness) :
Object3D::Object3D(albedos, colour, alpha, refractionIndex, shinyness) {
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

void Plane::intersect(const Ray3D &ray, double *lambda, Point3D *intersection, Point3D *normal, ColourRGB *colour) const {
    // Computes and returns the value of 'lambda' at the intersection
    // between the specified ray and the specified plane.
    
    /////////////////////////////////
    // TO DO: Complete this function.
    /////////////////////////////////
}
