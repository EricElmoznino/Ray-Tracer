#include "Plane.h"

Plane::Plane(const Material &material, const ColourRGB &colour) :
Object3D::Object3D(material, colour) {
}

ColourRGB Plane::colourAtLocalPoint(const Point3D &p) const {
    // If no texture, return this object's standard color
    if (textureImage.rgbImageData == NULL) {
        return colour;
    }
    
    double a = p.x + 0.5;
    double b = p.y + 0.5;
    return textureImage.textureMap(a, b);
}

Intersection Plane::intersect(const Ray3D &ray) {
    Intersection intersection;
    
    // Acquire ray in local coordinates
    Point3D rayOrigin = invTransform*ray.origin;
    Point3D rayDirection = invTransform*ray.direction;
    
    double denom = normal.dot(rayDirection);
    // Invalid intersection - plane is parallel to ray
    if (fabs(denom) < 1e-6) {
        intersection.none = true;
        return intersection;
    }

    double t = normal.dot(c - rayOrigin) / denom;
    // Invalid intersection - behind camera
    if (t < 0)
    {
    	intersection.none = true;
    	return intersection;
    }

    //Intersection point
    Point3D p = rayOrigin + t*rayDirection;

    //Check if intersects within plane's bounds
	if (p.x >= -.5 && p.x <= .5 && p.y >= -.5 && p.y <= .5)
	{
		Point3D hitNormalLocal = rayDirection.dot(normal) < 0 ? normal : -1*normal;

		intersection.none = false;
		intersection.insideObject = false;
		intersection.lambda = t;
		intersection.point = ray.rayPosition(t);
		intersection.normal = (invTransform.transpose() * hitNormalLocal).normalized();
		intersection.material = material;
		intersection.colour = colourAtLocalPoint(p);
        intersection.canSelfReflect = false;
		intersection.obj = this;

		return intersection;
	}
	intersection.none = true;
	return intersection;
}

bool Plane::doesIntersect(const Ray3D &ray) {
    return !intersect(ray).none;
}
