#ifndef PointLightSource_h
#define PointLightSource_h

#include <stdio.h>
#include <list>
#include "ColourRGB.h"
#include "Object3D.h"

using namespace std;

class PointLightSource {
public:
    ColourRGB colour;
    Point3D location;
    
    PointLightSource(const ColourRGB &colour, const Point3D &location);
    
    /*
     This function sets up and inserts a rectangular area light source
     with size (width, height)
     orientation given by the normal vector (normal)
     centered at (centre)
     consisting of (numHori X numVert) point light sources (uniformly sampled)
     and with (colour) - which also determines intensity
     
     Note that the light source is visible as a uniformly colored rectangle and
     casts no shadow. If you require a lightsource to shade another, you must
     make it into a proper solid box with backing and sides of non-light-emitting
     material
     */
    static void addAreaLight(float width, float height, Point3D normal, Point3D centre,
                             int numHori, int numVert, ColourRGB colour,
                             list<Object3D> *objects, list<PointLightSource> *lights);
};

#endif
