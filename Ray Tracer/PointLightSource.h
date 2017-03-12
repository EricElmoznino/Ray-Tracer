#ifndef PointLightSource_h
#define PointLightSource_h

#include <stdio.h>
#include "ColourRGB.h"
#include "Point3D.h"

class PointLightSource {
public:
    ColourRGB colour;
    Point3D location;
    PointLightSource *next; // Pointer to the next light in the scene
};

#endif
