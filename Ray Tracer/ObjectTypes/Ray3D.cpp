#include "Ray3D.h"

Point3D Ray3D::rayPosition(double lambda) const {
    return origin + lambda*direction;
}
