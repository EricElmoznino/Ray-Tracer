#ifndef Object3D_h
#define Object3D_h

#include <stdio.h>
#include "AlbedosPhong.h"
#include "ColourRGB.h"
#include "Image.h"
#include "Ray3D.h"
#include "Transform3D.h"

class Object3D {
public:
    AlbedosPhong albedos;
    ColourRGB colour;
    Transform3D transform;
    Transform3D invTransform;
    
    Image *textureImage;    // Pointer to the structure holding the texture for this object
    
    double alpha;   // Opacity - if less than 1 this is a semi transparent object
                        // and refraction rays should be implemented
    double refractionIndex;
    double shinyness;   // Exponent for phong specular component
    
    bool bothSidesLit;      // Flag to indicate that both sides of the object should be lit
    bool isAreaLightSource; // Flag to indicate if this is an area light source
    
    Object3D *next; // Pointer to the next entry in the object linked list
    
    // Texture mapping function. Takes normalized texture coordinates (a,b) and returns the
    // texture colour at that point using bi-linear interpolation
    void textureMap(Image *image, double a, double b,
                    double *red, double *green, double *blue);
    
    // Functions to subclass for different object types
    // (e.g. plane, sphere, etc.)
    
    // Note that the intersection function must compute the lambda at the intersection, the
    // intersection point p, the normal at that point n, and the texture coordinates (a,b).
    // The texture coordinates are not used unless texImg!=NULL and a textureMap function
    // has been provided
    virtual void intersect(const Ray3D &ray, double *lambda,
                           Point3D *intersection, Point3D *normal,
                           double *a, double *b) = 0;
};

#endif
