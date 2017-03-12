#include "Point3D.h"
#include "../ObjectTypes/Object3D.h"
#include <stdio.h>
#include <math.h>

Point3D::Point3D() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
    w = 1.0;    // default to point, even though can be vec if this is 0.0
}

Point3D::Point3D(double x, double y, double z, bool isVec) {
    this->x = x;
    this->y = y;
    this->z = z;
    isVec ? this->w = 0.0 : 1.0;
}

// Should only be called with vectors (w=0), since points don't have magnitudes
double Point3D::magnitude() const {
    return sqrt(this->dot(*this));
}

Point3D Point3D::normalized() const {
    return 1.0/(this->magnitude()) * (*this);
}

// Whenever this is called in order to compute the actual dot product, the contribution
// from the w components should be 0, since the dot product only makes sense with vectors.
// The reason that we still add it into the dot product over here is so that we can use this
// function in matrix multiplication.
double Point3D::dot(const Point3D &other) const {
    return this->x*other.x + this->y*other.y + this->z*other.z + this->w*other.w;
}

// Assume that this is called when either both inputs
// are points (w=1) or both inputs are vectors (w=0)
Point3D Point3D::crossUnit(const Point3D &other) const {
    return Point3D(this->y*other.z - this->z*other.y,
                other.x*this->z - other.z*this->x,
                this->x*other.y - this->y*other.x,
                this->w == 0.0 ? 0.0 : 1.0)
    .normalized();
}

Point3D Point3D::operator+(const Point3D &other) const {
    return Point3D(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w); // only really makes sense for vectors (w=0)
}

Point3D Point3D::operator-(const Point3D &other) const {
    return Point3D(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

Point3D Point3D::operator*(double scale) const {
    return Point3D(this->x * scale, this->y * scale, this->z * scale, this->w); // uniform scale transform does not effect w
}

bool Point3D::operator==(const Point3D &other) const {
    return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w;
}

bool Point3D::operator!=(const Point3D &other) const {
    return !(*(this) == other);
}

Point3D Point3D::linearInterpolate(const Point3D &end, double progress) const {
    Point3D difference = end - (*this);
    return (*this) + difference*progress;
}

Point3D Point3D::normalTransform(const Object3D &obj) const {
    ///////////////////////////////////////////
    // TO DO: Complete this function
    ///////////////////////////////////////////
    
    return Point3D();   // temporary to avoid errors
}

void Point3D::printPoint3D() const {
    printf("(%.2f, %.2f, %.2f, %.2f)\n", x, y, z, w);
}

Point3D operator*(double scale, const Point3D &p) {
    return p*scale;
}

Point3D::Point3D(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Point3D Point3D::homogeonized() const {
    if (this->w == 0.0) {
        return (*this);
    }
    else {
        return Point3D(this->x/this->w, this->y/this->w, this->z/this->w, 1.0);
    }
}
