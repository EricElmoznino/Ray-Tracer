#include "Sphere.h"

Sphere::Sphere(const Material &material, const ColourRGB &colour,
             double alpha, double refractionIndex, double shinyness) :
Object3D::Object3D(material, colour, alpha, refractionIndex, shinyness) {
    Object3D::bothSidesLit = false;
}

ColourRGB Sphere::colourAtLocalPoint(const Point3D &p) const {
    // If no texture, return this object's standard color
    if (textureImage == NULL) {
        return colour;
    }
    
    // TO DO: Complete this function. Will need to find the (a,b)
    // texture coordinates at p given this type of object and then
    // call Image's textureMap function
    return ColourRGB(0, 0, 0);  // temporary until function is implemented
}

Intersection Sphere::intersect(const Ray3D &ray) const {
    // Computes and returns the value of 'lambda' at the intersection
    // between the specified ray and the specified canonical sphere.
    Intersection intersection;
    intersection.material = material;   // For now, objects have only one uniform material
    
    /////////////////////////////////
    // TO DO: Complete this function.
    /////////////////////////////////
    
    return intersection;
}
