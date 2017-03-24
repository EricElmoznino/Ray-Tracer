#include <list>
#include <float.h>
#include "RayTracer.h"

void RayTracer::renderImage(View camera, list<Object3D*> objects, list<PointLightSource> lights,
                            int maxDepth, Image *output, char * name) {
    // Store local copies of these that way we don't have to keep passing them around
    // between the functions that do the actual ray tracing work
    this->objects = objects;
    this->lights = lights;
    this->maxDepth = maxDepth;
    
    // Itterate through all the pixels and do the ray tracing
    fprintf(stderr,"Rendering row: ");
    for (int i = 0; i < output->sx; i++)		// For each pixel in the image
    {
        fprintf(stderr,"%d/%d, ", i, output->sx);
        for (int j = 0; j < output->sy; j++)
        {
            ///////////////////////////////////////////////////////////////////
            // TO DO - complete the code that should be in this loop to do the
            //         raytracing!
            ///////////////////////////////////////////////////////////////////
            
            // Find the current ray
            Point3D origin(0, 0, 0, false);
            double xIncrement = ((i+0.5)/output->sx) * camera.wsize;
            double yIncrement = ((j+0.5)/output->sy) * camera.wsize;
            Point3D targetPixel(camera.wl + xIncrement,
                                camera.wt - yIncrement,
                                -1.0, false);
            Point3D direction = targetPixel - origin;
            Ray3D ray(camera.cameraToWorld * origin,
                      camera.cameraToWorld * direction);
            
            // Trace the pixel and store it in the image
            ColourRGB pixelColour = rayTrace(ray, camera.wsize / output->sx);
            output->setColourAtPixel(i, j, pixelColour);
        }
    }
    
    fprintf(stderr,"\nDone!\n");
    
    // Output rendered image
    output->outputImage(name);
}

ColourRGB RayTracer::rayTrace(Ray3D ray, double pixelSize) {
    if (antialiasingEnabled) {
        ColourRGB pixelColour(0, 0, 0);
        double subPixelSize = pixelSize / superSamplingResolution;
        for (int i = 0; i < superSamplingResolution; i++) {
            for (int j = 0; j < superSamplingResolution; j++) {
                // Compute a random x,y offset within the subPixelSize
                Point3D offset((double)rand()/RAND_MAX*subPixelSize - 0.5*subPixelSize,
                               (double)rand()/RAND_MAX*subPixelSize - 0.5*subPixelSize,
                               0, true);
                
                // Move the ray by the random offset
                Ray3D subRay = Ray3D(ray.origin, ray.direction + offset).normalized();
                
                // Cast the ray. We divide by the number of super-samples we have
                // in order to compute the average colour over all rays for this pixel
                pixelColour += rayTraceRecursive(subRay, maxDepth, NULL) *
                        (1.0 / (superSamplingResolution*superSamplingResolution));
            }
        }
        
        return pixelColour;
    }
    
    else {
        ray = ray.normalized();
        return rayTraceRecursive(ray, maxDepth, NULL);
    }
}

ColourRGB RayTracer::rayTraceRecursive(const Ray3D &ray, int depth, const Object3D *source) {
    ///////////////////////////////////////////////////////
    // TO DO: Complete this function. Refer to the notes
    // if you are unsure what to do here.
    ///////////////////////////////////////////////////////
    
    Intersection firstHit = findFirstHit(ray, source);
    if (firstHit.none) {
        return ColourRGB(0, 0, 0);  // Probably will change latter to be the skybox
    }
    else if (firstHit.isLight) {    // Lights just emmit their colour
        return firstHit.colour;
    }
    
    return shade(firstHit, ray, depth);
}

ColourRGB RayTracer::shade(const Intersection &intersection, const Ray3D &ray, int depth) {
    ColourRGB res(0.0, 0.0, 0.0);
    
    //////////////////////////////////////////////////////////////
    // TO DO: Implement this function. Refer to the notes for
    // details about the shading model.
    //////////////////////////////////////////////////////////////
    
    res += phongModel(intersection, ray);
    
    if (depth > 0) {
        res += reflection(intersection, ray, depth - 1);
    }
    
    return res;
}

Intersection RayTracer::findFirstHit(const Ray3D &ray, const Object3D *source) {    
	// Find the closest intersection between the ray and any objects in the scene.
	// It returns:
	//   - The lambda at the intersection (or < 0 if no intersection)
	//   - The pointer to the object at the intersection (so we can evaluate the colour in the shading function)
	//   - The location of the intersection point (in p)
	//   - The normal at the intersection point (in n)
	//
	// Os is the 'source' object for the ray we are processing, can be NULL, and is used to ensure we don't 
	// return a self-intersection due to numerical errors for recursive raytrace calls.
	//

	/////////////////////////////////////////////////////////////
	// TO DO: Implement this function. See the notes for
	// reference of what to do in here
	/////////////////////////////////////////////////////////////
    
	double closestDistance = DBL_MAX;
	Intersection closestIntersection;
    closestIntersection.none = true;

	for (auto it = objects.begin(); it != objects.end(); it++)
	{
        Object3D *object = *it;
		Intersection intersection = object->intersect(ray);
		if (!intersection.none) {
			double distance = (intersection.point - ray.origin).magnitude();
			if (distance < closestDistance && intersection.obj != source) {
				closestDistance = distance;
				closestIntersection = intersection;
			}
		}
	}
    
    return closestIntersection;
}

ColourRGB RayTracer::phongModel(const Intersection &intersection, const Ray3D &ray) {
    ColourRGB phongColour(0, 0, 0);
    
    // Ambient component
    // Not effected by lights or shadows. Always constant.
    double ambient = intersection.material.ambient;
    ColourRGB ambientColour = ColourRGB(1, 1, 1) * ambient;
    phongColour += ambientColour.filter(intersection.colour);
    
    list<PointLightSource>::iterator light;
    for (light=lights.begin(); light!=lights.end(); light++)
    {
        if (!isInShadow(intersection, *light)) {
            // Note: Light have the same Ia, Id, and Is,
            // which for every colour component is equal
            // to the light's magnitude of that colour.
            // i.e. Iar = light.red, Iab = light.blue,
            //      Is.b = light.blue, etc.
            
            //Diffuse component
            Point3D s = (light->location - intersection.point).normalized();    // light direction
            double n_dot_s = (intersection.normal).dot(s);
            double mag_diffuse = (0 < n_dot_s)?n_dot_s:0;
            double diffuse = (intersection.material.diffuse)*mag_diffuse;
            ColourRGB diffuseColour = light->colour * diffuse;
            
            //Specular component
            Point3D r = -1*s + 2*intersection.normal*s.dot(intersection.normal);    // reflection direction
            Point3D b = -1 * ray.direction;
            double mag_spec = (0 < r.dot(b))?r.dot(b):0;
            mag_spec = pow(mag_spec, intersection.material.shinyness);
            double specular = (intersection.material.specular)*mag_spec;
            ColourRGB specularColour = light->colour * specular;
            
            // Filter the ambient and diffuse components by the object's
            // colour, but the specular should just be a pure reflectance
            // of the light's colour
            phongColour +=  diffuseColour.filter(intersection.colour) +
                            specularColour;
        }
    }
    
    return phongColour;
}

bool RayTracer::isInShadow(const Intersection &intersection, const PointLightSource &light) {
    // Create the shadow ray
    Point3D origin = intersection.point;
    Point3D direction = (light.location - origin).normalized();
    Ray3D shadowRay = Ray3D(origin, direction);
    
    // Bias the ray's origin slightly away from the object
    // in order to avoid errors from numerical precision.
    // We can't simply rely on the source object here, because
    // it's perfectly legal for an object to be casting itself
    // partly in shadow (e.g. the backside of an object)
    shadowRay = shadowRay.bias(intersection.normal);
    
    Intersection firstHit = findFirstHit(shadowRay, NULL);
    return !firstHit.none;
}

ColourRGB RayTracer::reflection(const Intersection &intersection, const Ray3D &ray, int depth) {
	Point3D r;
	
	if (glossyreflEnabled) {
		double roughness = 0.1; // Added as a material property later for glossy reflections.

		Point3D s = (light->location - intersection.point).normalized();    // light direction
		r = (-1 * s + 2 * intersection.normal*s.dot(intersection.normal)).normalized();    // reflection direction

		// Create orthonormal basis at intersection point
		Point3D u = r.crossUnit(intersection.normal);
		Point3D v = r.crossUnit(intersection.normal);

		// Choose uniformly sampled random direction to send the ray in
		double theta = 2 * M_PI * drand48() * roughness;
		double phi = 2 * M_PI * drand48() * roughness;
		double x = sin(theta)*cos(phi);
		double y = sin(theta)*sin(phi);
		double z = cos(theta);

		// Convert sample to world coord using the orthonormal basis
		r = (x * u + y * v + z * r).normalized();
	}

	else {
		r = ray.direction - 2 * intersection.normal*ray.direction.dot(intersection.normal);
	}

	Ray3D reflectionRay(intersection.point, r);
	return rayTraceRecursive(reflectionRay, depth, intersection.obj) * intersection.material.global;
}
