#include "Plane.h"

Plane::Plane(const AlbedosPhong &albedos, const ColourRGB &colour,
             double alpha, double refractionIndex, double shinyness) :
Object3D::Object3D(albedos, colour, alpha, refractionIndex, shinyness) {
    Object3D::bothSidesLit = true;
}

void Plane::intersect(const Ray3D &ray, double *lambda, Point3D *intersection, Point3D *normal, double *a, double *b) const {
    // Computes and returns the value of 'lambda' at the intersection
    // between the specified ray and the specified plane.
    
    /////////////////////////////////
    // TO DO: Complete this function.
    /////////////////////////////////
}

ColourRGB Plane::textureMap(double a, double b) const {
    /*
     Function to determine the colour of a textured object at
     the normalized texture coordinates (a,b).
     
     a and b are texture coordinates in [0 1].
     img is a pointer to the image structure holding the texture for
     a given object.
     
     The colour is returned in R, G, B. Uses bi-linear interpolation
     to determine texture colour.
     */
    
    //////////////////////////////////////////////////
    // TO DO (Assignment 4 only):
    //
    //  Complete this function to return the colour
    // of the texture image at the specified texture
    // coordinates. Your code should use bi-linear
    // interpolation to obtain the texture colour.
    //////////////////////////////////////////////////
    
    if (textureImage == NULL) {
        return ColourRGB(0.0, 0.0, 0.0);    // no texture, return black
    }
    
    return ColourRGB(0.0, 0.0, 0.0);	// Returns black - delete this and
    // replace with your code to compute
    // texture colour at (a,b)
}
