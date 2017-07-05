#include "Camera.h"

Camera::Camera(const Point3D &e, const Point3D &g, const Point3D &up,
     double f, double wsize) {
    // Setup camera position and basis vectors
    Point3D w = (-1*g).normalized();
    Point3D u = w.crossUnit(up);
    Point3D v = u.crossUnit(w);
    
    // Copy focal length and window size parameters
    this->f = f;
    this->wsize = wsize;
    
    // Setup coordinate conversion matrices
    cameraToWorld = Transform3D(u.x, v.x, w.x, e.x,
                                u.y, v.y, w.y, e.y,
                                u.z, v.z, w.z, e.z,
                                0.0, 0.0, 0.0, 1.0);
    worldToCamera = Transform3D(u.x, u.y, u.z, -u.dot(e),
                                v.x, v.y, v.z, -v.dot(e),
                                w.x, w.y, w.z, -w.dot(e),
                                0.0, 0.0, 0.0, 1.0);
}

Transform3D Camera::getTransform() {
    return cameraToWorld;
}

Camera Camera::translate(double x, double y, double z) {
    cameraToWorld = Transform3D::translated(x, y, z) * cameraToWorld;
    worldToCamera = cameraToWorld.inverse();
    return *this;
}

Camera Camera::orient(double yaw, double pitch, double roll) {
    cameraToWorld = Transform3D::rotatedZ(roll)*Transform3D::rotatedX(pitch)*Transform3D::rotatedY(yaw) * cameraToWorld;
    worldToCamera = cameraToWorld.inverse();
    return *this;
}
