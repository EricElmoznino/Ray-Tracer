#include "PointLightSource.h"

PointLightSource::PointLightSource(const ColourRGB &colour, const Point3D &location) :
colour(colour), location(location) {}

void PointLightSource::addAreaLight(float width, float height, Point3D normal, Point3D centre,
                         int numHori, int numVert, ColourRGB colour,
                         list<Object3D*> &objects, list<PointLightSource> &lights) {
    /////////////////////////////////////////////////////
    // TO DO: (Assignment 4!)
    // Implement this function to enable area light sources
    /////////////////////////////////////////////////////
    
    
}
