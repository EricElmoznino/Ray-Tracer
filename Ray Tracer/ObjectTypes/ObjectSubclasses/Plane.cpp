#include "Plane.h"

Plane::Plane(const Material &material, const ColourRGB &colour) :
Object3D::Object3D(material, colour) {
    Object3D::isLight = false;
}

ColourRGB Plane::colourAtLocalPoint(const Point3D &p) const {
    // If no texture, return this object's standard color
    if (textureImage.rgbImageData == NULL) {
        return colour;
    }
    
    double a = (p.x - p3.x) / (p1.x - p3.x);
    double b = (p.y - p3.y) / (p1.y - p3.y);
    return textureImage.textureMap(a, b);
}

Intersection Plane::intersect(const Ray3D &ray) {
    Intersection intersection;
    
    // Acquire ray in local coordinates
    Point3D rayOrigin = invTransform*ray.origin; //e
    Point3D rayDirection = invTransform*ray.direction; //d

    double t = -rayOrigin.z/rayDirection.z;

    //Invalid intersection - behind camera
    if (t < 0 || rayDirection.z == 0)
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
		intersection.isLight = Object3D::isLight;
		intersection.insideObject = false;
		intersection.lambda = t;
		intersection.point = ray.rayPosition(t);
		intersection.normal = (invTransform.transpose() * hitNormalLocal).normalized();
		intersection.material = material;
		intersection.colour = colourAtLocalPoint(p);
		intersection.obj = this;

		return intersection;
	}
	intersection.none = true;
	return intersection;
}
