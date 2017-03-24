#include "PlaneLightSource.h"

PlaneLightSource::PlaneLightSource(const ColourRGB colour) :
Plane::Plane(Material(), colour) {
    Object3D::bothSidesLit = true;
    Object3D::isLight = true;
}
