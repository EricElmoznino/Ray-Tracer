#include "PointLightSource.h"

PointLightSource::PointLightSource(const ColourRGB &colour, const Point3D &location) :
colour(colour), location(location) {}

void PointLightSource::addAreaLight(float width, float height, const Point3D &normal,
                                    const Point3D &xUnit, const Point3D &centre,
                                    int numHori, int numVert, const ColourRGB &colour,
                                    list<Object3D*> &objects, list<PointLightSource> &lights) {
    /////////////////////////////////////////////////////
    // TO DO: (Assignment 4!)
    // Implement this function to enable area light sources
    /////////////////////////////////////////////////////
    
    // Make sure the normal and xUnit are normalized (just in case)
    // and find the y basis vector
    Point3D zBasis = normal.normalized();
    Point3D xBasis = xUnit.normalized();
    Point3D yBasis = zBasis.crossUnit(xBasis);
    
    // Place the actual point light sources
    Point3D botLeftCorner = centre - (width/2)*xBasis - (height/2)*yBasis;
    double deltaX = width / numHori;
    double deltaY = height / numVert;
    for (int i = 0; i < numHori; i++) {
        for (int j = 0; j < numVert; j++) {
            Point3D lightLocation = botLeftCorner +
                            (i+0.5)*deltaX*xBasis +
                            (j+0.5)*deltaY*yBasis;
            PointLightSource light(colour * (1.0/(numHori*numVert)), lightLocation);
            lights.push_back(light);
        }
    }
    
    // TODO: Add the actual PlaneLightSource object
}
