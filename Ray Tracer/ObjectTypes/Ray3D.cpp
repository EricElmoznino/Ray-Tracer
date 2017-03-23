#include "Ray3D.h"

Ray3D::Ray3D(Point3D origin, Point3D direction) {
    this->origin = origin;
    this->direction = direction;
}

Point3D Ray3D::rayPosition(double lambda) const {
    return origin + lambda*direction;
}
