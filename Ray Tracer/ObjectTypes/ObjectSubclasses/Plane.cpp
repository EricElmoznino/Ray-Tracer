#include "Plane.h"

Plane::Plane(const AlbedosPhong &albedos, const ColourRGB &colour,
             double alpha, double refractionIndex, double shinyness) :
Object3D::Object3D(albedos, colour, alpha, refractionIndex, shinyness) {
    Object3D::bothSidesLit = true;
}

void Plane::intersect(const Ray3D &ray, double *lambda, Point3D *intersection, Point3D *normal, double *a, double *b) {
    // Computes and returns the value of 'lambda' at the intersection
    // between the specified ray and the specified plane.
    
    /////////////////////////////////
    // TO DO: Complete this function.
    /////////////////////////////////
}
