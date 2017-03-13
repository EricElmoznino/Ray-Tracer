#ifndef Object3D_h
#define Object3D_h

#include <stdio.h>
#include "AlbedosPhong.h"
#include "ColourRGB.h"
#include "Image.h"
#include "Ray3D.h"
#include "../GeometricTypes/Transform3D.h"

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
    
    Object3D(const AlbedosPhong &albedos, const ColourRGB &colour,
             double alpha, double refractionIndex, double shinyness);
    Object3D(const Object3D &obj);
    virtual ~Object3D();
    
    Object3D& operator=(const Object3D &obj);
    
    // Texture mapping function. Takes normalized texture coordinates (a,b) and returns the
    // texture colour at that point using bi-linear interpolation
    ColourRGB textureMap(double a, double b) const;
    
    // Functions to subclass for different object types
    // (e.g. plane, sphere, etc.)
    
    // Note that the intersection function must compute the lambda at the intersection, the
    // intersection point p, the normal at that point n, and the texture coordinates (a,b).
    // The texture coordinates are not used unless texImg!=NULL and a textureMap function
    // has been provided.
    // This has an empty implementation because it is supposed to be
    virtual void intersect(const Ray3D &ray, double *lambda,
                           Point3D *intersection, Point3D *normal,
                           double *a, double *b) {;};
    
    
    // WARNING: These methods are mutable, meaning that they change the
    // data in the class. I don't like this style, but it is necessary
    // for efficiency
    void rotateX(double theta);
    void rotateY(double theta);
    void rotateZ(double theta);
    void translate(double x, double y, double z);
    void scale(double x, double y, double z);
    
    // Having a function like this means that at any given point
    // before calling it, the invTransform might be invalid.
    // This is necessary to avoid unecessary computations which
    // would occur if we updated the inverse every time we updated
    // the transform.
    void updateInverse();
    
    // Load a texture image from file and assign it to this object
    void loadTexture(const char *filename);
};

#endif
