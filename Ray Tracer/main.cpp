/*
 CSC418 - RayTracer code - Winter 2017 - Assignment 3&4
 
 Written Dec. 9 2010 - Jan 20, 2011 by F. J. Estrada
 Freely distributable for adacemic purposes only.
 
 Uses Tom F. El-Maraghi's code for computing inverse
 matrices. You will need to compile together with
 svdDynamic.c
 
 You need to understand the code provided in
 this file, the corresponding header file, and the
 utils.c and utils.h files. Do not worry about
 svdDynamic.c, we need it only to compute
 inverse matrices.
 
 You only need to modify or add code in sections
 clearly marked "TO DO"
 */

#include <stdio.h>
#include <list>
#include "RayTracer.h"
#include "ObjectTypes/ObjectSubclasses/Plane.h"
#include "ObjectTypes/ObjectSubclasses/Sphere.h"
#include "ObjectTypes/ObjectSubclasses/TriangleMesh.h"
#include "Lights/PointLightSource.h"
#include "Lights/AreaLightElement.h"

#define PI 3.14159265354

using namespace std;

// A couple of global structures and data: An object list, a light list, and the
// maximum recursion depth
list<Object3D*> objects;        // has to be a list of pointers for polymorphic Object3D subclasses
list<Light*> lights;            // has to be a list of pointers for polymorphic Light subclasses
int MAX_DEPTH;

void buildScene(void)
{
    // Sets up all objects in the scene. This involves creating each object,
    // defining the transformations needed to shape and position it as
    // desired, specifying the reflectance properties (material and colours)
    // and setting up textures where needed.
    // Light sources must be defined, positioned, and their colour defined.
    // All objects must be inserted in the object_list. All light sources
    // must be inserted in the light_list.
    //
    // To create hierarchical objects:
    //   Copy the transform matrix from the parent node to the child, and
    //   apply any required transformations afterwards.
    //
    // NOTE: After setting up the transformations for each object, don't
    //       forget to set up the inverse transform matrix!
    
    ///////////////////////////////////////
    // TO DO: For Assignment 3 you have to use
    //        the simple scene provided
    //        here, but for Assignment 4 you
    //        *MUST* define your own scene.
    //        Part of your mark will depend
    //        on how nice a scene you
    //        create. Use the simple scene
    //        provided as a sample of how to
    //        define and position objects.
    ///////////////////////////////////////
    
    // Simple scene for Assignment 3:
    // Insert a couple of objects. A plane and two spheres
    // with some transformations.
    
    // Let's add a plane
    // Note the plane is highly-reflective (rs=rg=.75) so we
    // should see some reflections if all is done properly.
    // Colour is close to cyan, and currently the plane is
    // completely opaque (alpha=1). The refraction index is
    // meaningless since alpha=1
    Object3D *obj = new Plane(Material(0.05, 0.75, 0.05, 0.05, 1, 1, 2, 0.3),  // original
                              ColourRGB(0.55, 0.8, 0.75));
    obj->scale(12, 12, 2);
    obj->rotateZ(PI/1.20);
    obj->rotateX(PI/2.25);
    obj->translate(0, -3, 10);
    obj->updateInverse();       // Very important! compute
    // and store the inverse
    // transform for this object!
    obj->loadTexture("Textures/greyscale_natural_grunge2.ppm");
    objects.push_front(obj);    // Insert into object list
    
    // Let's add a couple spheres
    /*obj = new Sphere(Material(0.05, 0.95, 0.35, 0.35, 1, 1, 6, 0.3),
                     ColourRGB(1.0, 0.25, 0.25));
    obj->scale(0.75, 0.5, 1.5);
    obj->rotateY(PI/2.0);
    obj->translate(-1.45, 1.1, 3.5);
    obj->updateInverse();
    obj->loadTexture("Textures/webtreats_stone_5.ppm");
    objects.push_front(obj);*/
    
    obj = new Sphere(Material(0.05, 0.95, 0.95, 0.75, 1, 1, 6, 0.3),
                     ColourRGB(0.75, 0.95, 0.55));
    obj->scale(0.5, 2.0, 1.0);
    obj->rotateZ(PI/1.5);
    obj->translate(1.75, 1.25, 5.0);
    obj->updateInverse();
    obj->loadTexture("Textures/webtreats_stone_4.ppm");
    objects.push_front(obj);
    
    // Test sphere
//    Object3D *obj = new Sphere(Material(0.0, 0.0, 0.0, 0.0, 0.0, 1.4, 6, 0.1),
//                               ColourRGB(0.9, 0.9, 0.9));
//    obj->scale(1.0, 1.0, 1.0);
//    obj->translate(0.0, -3.0, 7.0);
//    obj->updateInverse();
//    objects.push_front(obj);
//    obj = new Plane(Material(0.05, 0.95, 0.35, 0.0, 1, 1, 6, 0.3),
//                    ColourRGB(1.0, 0.25, 0.25));
    


    // Insert a single point light source.
    PointLightSource *light = new PointLightSource(ColourRGB(0.95, 0.95, 0.95),       // original
                                                   Point3D(0.0, 15.5, -5.5, false));
    lights.push_front(light);
//    AreaLightElement::addAreaLight(5, 5, Point3D(0, -1, 0, true), Point3D(1, 0, 0, true),
//                                   Point3D(0.0, 15.5, -5.5, false), 8, 8,
//                                   ColourRGB(0.95, 0.95, 0.95), lights);
    
    // End of simple scene for Assignment 3
    // Keep in mind that you can define new types of objects such as cylinders and parametric surfaces,
    // or, you can create code to handle arbitrary triangles and then define objects as surface meshes.
    //
    // Remember: A lot of the quality of your scene will depend on how much care you have put into defining
    //           the relflectance properties of your objects, and the number and type of light sources
    //           in the scene.

    // Test OBJ
    obj = new TriangleMesh("OBJ/poly.obj",Material(0.05, 0.95, 0.35, 0.35, 1, 1, 6, 0.3),
            ColourRGB(1.0, 0.25, 0.25));
    //obj->scale(0.75, 0.5, 1.5);
	//obj->rotateY(PI/2.0);
	obj->translate(-1.45, 1.1, 3.5);
	obj->updateInverse();
	objects.push_front(obj);
}

int main(int argc, char *argv[])
{
    // Main function for the raytracer. Parses input parameters,
    // sets up the initial blank image, and calls the functions
    // that set up the scene and do the raytracing.
    Image *im;          // Will hold the raytraced image
    int sx;             // Size of the raytraced image
    int antialiasing;	// Flag to determine whether antialiaing is enabled or disabled
    char output_name[1024];	// Name of the output file for the raytraced .ppm image
    Point3D e;          // Camera view parameters 'e', 'g', and 'up'
    Point3D g;
    Point3D up;
    ColourRGB background(0.0, 0.0, 0.0);// Background colour
    RayTracer rayTracer;    // The ray tracer
    
    if (argc<5)
    {
        fprintf(stderr,"RayTracer: Can not parse input parameters\n");
        fprintf(stderr,"USAGE: RayTracer size rec_depth antialias output_name\n");
        fprintf(stderr,"   size = Image size (both along x and y)\n");
        fprintf(stderr,"   rec_depth = Recursion depth\n");
        fprintf(stderr,"   antialias = A single digit, 0 disables antialiasing. Anything else enables antialiasing\n");
        fprintf(stderr,"   output_name = Name of the output file, e.g. MyRender.ppm\n");
        exit(0);
    }
    sx=atoi(argv[1]);
    MAX_DEPTH=atoi(argv[2]);
    if (atoi(argv[3])==0) antialiasing=0; else antialiasing=1;
    strcpy(&output_name[0],argv[4]);
    
    fprintf(stderr,"Rendering image at %d x %d\n",sx,sx);
    fprintf(stderr,"Recursion depth = %d\n",MAX_DEPTH);
    if (!antialiasing) fprintf(stderr,"Antialising is off\n");
    else fprintf(stderr,"Antialising is on\n");
    fprintf(stderr,"Output file name: %s\n",output_name);
    
    // Allocate memory for the new image
    im = new Image(sx, sx);
    
    ///////////////////////////////////////////////////
    // TO DO: You will need to implement several of the
    //        functions below. For Assignment 3, you can use
    //        the simple scene already provided. But
    //        for Assignment 4 you need to create your own
    //        *interesting* scene.
    ///////////////////////////////////////////////////
    buildScene();		// Create a scene. This defines all the
                            // objects in the world of the raytracer
    
    //////////////////////////////////////////
    // TO DO: For Assignment 3 you can use the setup
    //        already provided here. For Assignment 4
    //        you may want to move the camera
    //        and change the view parameters
    //        to suit your scene.
    //////////////////////////////////////////
    
    // Camera center is at (0,0,-3)
    e = Point3D(0.0, 0.0, -3.0, false);
    
    // To define the gaze vector, we choose a point 'pc' in the scene that
    // the camera is looking at, and do the vector subtraction pc-e.
    // Here we set up the camera to be looking at the origin
    g = Point3D(0.0, 0.0, 0.0, false) - e;
    
    // Define the 'up' vector to be the Y axis
    up = Point3D(0, 1, 0, true);
    
    // Set up view with given the above vectors, a 4x4 window,
    // and a focal length of -1 (why? where is the image plane?)
    // Note that the top-left corner of the window is at (2, 2)
    // in camera coordinates.
    View cam(e, g, up, -3, 4);
    
    // Setup the skybox
    Skybox *skybox = NULL;
    skybox = new Skybox("Skyboxes/lagoon_lf.ppm", "Skyboxes/lagoon_rt.ppm",
                        "Skyboxes/lagoon_dn.ppm", "Skyboxes/lagoon_up.ppm",
                        "Skyboxes/lagoon_bk.ppm", "Skyboxes/lagoon_ft.ppm");
    
    fprintf(stderr,"View parameters:\n");
    fprintf(stderr,"Width=%f, f=%f\n", cam.wsize,cam.f);
    fprintf(stderr,"Camera to world conversion matrix (make sure it makes sense!):\n");
    cam.cameraToWorld.printTransform3D();
    fprintf(stderr,"World to camera conversion matrix\n");
    cam.worldToCamera.printTransform3D();
    fprintf(stderr,"\n");
    
    // Render the image with ray tracing
    rayTracer.skybox = skybox;
    rayTracer.maxDepth = MAX_DEPTH;
    rayTracer.antialiasingEnabled = antialiasing;
    rayTracer.superSamplingResolution = 5;
    rayTracer.glossyreflEnabled = true;
    rayTracer.refractionEnabled = true;
    rayTracer.renderImage(cam, objects, lights, im, output_name);
    
    // Exit section. Clean up and return.
    delete im;
    if (skybox != NULL) {
        delete skybox;
    }
    while (!objects.empty()) {
        delete objects.front();
        objects.pop_front();
    }
    while (!lights.empty()) {
        delete lights.front();
        lights.pop_front();
    }
    return 0;
}
