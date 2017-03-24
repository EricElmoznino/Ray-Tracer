#ifndef Object3D_h
#define Object3D_h

#include <stdio.h>
#include "Intersection.h"
#include "Image.h"
#include "Ray3D.h"
#include "../GeometricTypes/Transform3D.h"

class Object3D {
protected:
    bool isLight;       // Flag to indicate if this object is a light
    bool bothSidesLit;  // Flag to indicate that both sides of the object should be lit
    
    // Helper function for intersect. Given a point in the object's local coordinate
    // system, computes the color at that point (which potentially comes from a texture).
    // Obviously, the color will depend on the shape of the object, which is why this
    // function must be inherited and implemented.
    // NOTE: This function takes a point in LOCAL (object's) coordinate system
    virtual ColourRGB colourAtLocalPoint(const Point3D &p) const = 0;
    
public:
    Material material;
    ColourRGB colour;
    Transform3D transform;      // Model -> World
    Transform3D invTransform;   // World -> Model
    
    Image *textureImage;    // Pointer to the structure holding the texture for this object
    
    bool isLightSource();   // Scene objects can be lights
    
    Object3D(const Material &material, const ColourRGB &colour);
    Object3D(const Object3D &obj);
    virtual ~Object3D();
    
    Object3D& operator=(const Object3D &obj);
    
    // Functions to subclass for different object types
    // (e.g. plane, sphere, etc.)
    
    // Note that the intersection function must compute the lambda at the intersection, the
    // intersection point p, the normal at that point n, and the object color.
    // This has an empty implementation because it is supposed to be overriden by a subclass
    virtual Intersection intersect(const Ray3D &ray) = 0;
    
    // WARNING: These methods are mutable, meaning that they change the
    // data in the class. I don't like this style, but it is necessary
    // for efficiency
    void rotateX(double theta);
    void rotateY(double theta);
    void rotateZ(double theta);
    void translate(double x, double y, double z);
    void scale(double x, double y, double z);
    
    Point3D originInWorld() const;
    
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
