#include <list>
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
            ColourRGB pixelColor = rayTrace(ray);
            output->setColorAtPixel(i, j, pixelColor);
        }
    }
    
    fprintf(stderr,"\nDone!\n");
    
    // Output rendered image
    output->outputImage(name);
}

ColourRGB RayTracer::rayTrace(const Ray3D &ray) {
    return rayTraceRecursive(ray, maxDepth, NULL);
}

ColourRGB RayTracer::rayTraceRecursive(const Ray3D &ray, int depth, const Object3D *source) {
    ///////////////////////////////////////////////////////
    // TO DO: Complete this function. Refer to the notes
    // if you are unsure what to do here.
    ///////////////////////////////////////////////////////
    
    // End the recursive calls and return a black colour
    // that will have no contribution
    if (depth <= 0) {
        return ColourRGB(0, 0, 0);
    }
    
    Intersection firstHit = findFirstHit(ray, source);
    return shade(firstHit, ray, depth);
}

ColourRGB RayTracer::shade(const Intersection &intersection, const Ray3D &ray, int depth) {
    ColourRGB res(0.0, 0.0, 0.0);
    
    //////////////////////////////////////////////////////////////
    // TO DO: Implement this function. Refer to the notes for
    // details about the shading model.
    //////////////////////////////////////////////////////////////
    
    return res;
}

Intersection RayTracer::findFirstHit(const Ray3D &ray, const Object3D *source) {
    Intersection intersection;
    
    /////////////////////////////////////////////////////////////
    // TO DO: Implement this function. See the notes for
    // reference of what to do in here
    /////////////////////////////////////////////////////////////
    
    return intersection;
}

// PLACE FUNCTIONS TO CALCULATE PHONG ILLUMINATION, REFLECTION, REFRACTION, SHADOWS, ETC. BELOW HERE
// AND MAKE THEM PRIVATE MEMBERS IN THE HEADER SO THAT shade() DOESN'T BECOME UNMANAGEABLY LARGE
