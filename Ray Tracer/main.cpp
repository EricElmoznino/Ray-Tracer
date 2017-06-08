#include <stdio.h>
#include <list>
#include "RayTracer.h"
#include "ObjectTypes/ObjectSubclasses/Plane.h"
#include "ObjectTypes/ObjectSubclasses/Sphere.h"
#include "ObjectTypes/ObjectSubclasses/Cylinder.h"
#include "ObjectTypes/ObjectSubclasses/Cube.h"
#include "ObjectTypes/ObjectSubclasses/Cone.h"
#include "ObjectTypes/ObjectSubclasses/Paraboloid.h"
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

// MACHINE LEARNING CODE
void buildSceneML(void)
{
    Object3D *obj = new Plane(Material(0.05, 0.65, 0.05, 0.5, 1, 1, 2, 0.3),  // original
                              ColourRGB(0.55, 0.8, 0.75));
    obj->scale(12, 12, 2);
    obj->rotateZ(PI/1.20);
    obj->rotateX(PI/2.25);
    obj->translate(0, -3, 10);
    obj->loadTexture("Textures/greyscale_natural_grunge2.ppm");
    objects.push_front(obj);
    
    obj = new Paraboloid(Material::Chrome(),
                       ColourRGB(1.0, 0.25, 0.25));
    obj->scale(1, 1, 1);
    obj->rotateX(-0.5*PI/4);
    obj->rotateY(4*PI/4);
    obj->translate(0, -2, 5.5);
    objects.push_front(obj);
    
    PointLightSource *light = new PointLightSource(ColourRGB(0.95, 0.95, 0.95),
                                                   Point3D(0.0, 15.5, -5.5, false));
    lights.push_front(light);

}

int main(int argc, char *argv[])
{
    Image *im;
    int sx;
    int antialiasing;
    char output_name[1024];
    Point3D e;
    Point3D g;
    Point3D up;
    ColourRGB background(0.0, 0.0, 0.0);
    RayTracer rayTracer;
    
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
    
    buildSceneML();
    
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
    Camera cam(e, g, up, -3, 4);
    
    fprintf(stderr,"View parameters:\n");
    fprintf(stderr,"Width=%f, f=%f\n", cam.wsize,cam.f);
    fprintf(stderr,"Camera to world conversion matrix (make sure it makes sense!):\n");
    cam.cameraToWorld.printTransform3D();
    fprintf(stderr,"World to camera conversion matrix\n");
    cam.worldToCamera.printTransform3D();
    fprintf(stderr,"\n");
    
    // Render the image with ray tracing
    rayTracer.skybox = new Skybox("Skyboxes/lagoon_lf.ppm", "Skyboxes/lagoon_rt.ppm",
                                  "Skyboxes/lagoon_dn.ppm", "Skyboxes/lagoon_up.ppm",
                                  "Skyboxes/lagoon_bk.ppm", "Skyboxes/lagoon_ft.ppm");
    rayTracer.maxDepth = MAX_DEPTH;
    rayTracer.antialiasingEnabled = antialiasing;
    rayTracer.superSamplingResolution = 5;
    rayTracer.glossyreflEnabled = false;
    rayTracer.refractionEnabled = true;
    rayTracer.blurEnabled = false;
    rayTracer.renderImage(cam, objects, lights, im, output_name);
    
    // Exit section. Clean up and return.
    delete im;
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

//void buildStillLife(void)
//{
//    // BACKGROUND
//    Object3D *obj = new Plane(Material(0.05, 0.95, 0.0, 0.2, 1, 15, 0, 0.3),
//                              ColourRGB(1.0, 0.25, 0.25));
//    double height = 25, aspectRatio = 2560.0/1600, distance = 10;
//    obj->scale(height*aspectRatio, height, 1);
//    obj->translate(0, 10, distance);
//    obj->loadTexture("Textures/BACKGROUND_OIL.ppm");
//    objects.push_front(obj);
//    
//    //Kinda Shiny King
//    vector<Material> kingMaterials(1, Material::FrostedGlass());
//    vector<ColourRGB> kingColours(1, ColourRGB(1.0, 1.0, 1.0));
//    TriangleMesh *king = new TriangleMesh("OBJ/high_res_king.obj", kingMaterials, kingColours);
//    king->scale(1.05, 1.05, 1.05);
//    king->rotateX(-PI / 25);
//    king->rotateY(PI);
//    king->rotateZ(-PI/27);
//    king->translate(-0.3, -0.257, -1.65);
//
//    objects.push_front(king);
//
//    //Matte Horse
//    vector<Material> horseMaterials(1, Material(0.0, 0.2, 1.0, 0.2, 1.0, 1.0, 3, 0.1));
//    vector<ColourRGB> horseColours(1, ColourRGB(0.25, 0.25, 0.25));
//    TriangleMesh *horse = new TriangleMesh("OBJ/high_res_horse.obj", horseMaterials, horseColours);
//    horse->scale(1, 1, 1);
//    horse->rotateX(PI / 25);
//    horse->rotateY(PI);
//    horse->translate(0.3, 0.12, -1.0);
//
//    objects.push_front(horse);
//
//    //Glass Pawn
//    vector<Material> pawnMaterials(1, Material::Glass());
//    vector<ColourRGB> pawnColours(1, ColourRGB(1.0, 1.0, 1.0));
//    TriangleMesh *pawn = new TriangleMesh("OBJ/high_res_pawn.obj", pawnMaterials, pawnColours);
//    pawn->scale(.85, .85, .85);
//    pawn->rotateX(-PI / 25);
//    pawn->translate(-0.5, 0.04, -0.85);
//
//    objects.push_front(pawn);
//    
//    //Chrome Queen
//    vector<Material> queenMaterials(1, Material::Chrome());
//    vector<ColourRGB> queenColours(1, ColourRGB(0.155, 0.12, 0.12));
//    TriangleMesh *tri = new TriangleMesh("OBJ/high_res_queen.obj", queenMaterials, queenColours);
//    tri->scale(1.05, 1.05, 1.05);
//    tri->rotateX(-PI / 25);
//    tri->translate(0.5, 0.063, -1.63);
//
//    objects.push_front(tri);
//
//    //Table
//    vector<Material> tableMaterials(1, Material(0.25, 1.0, 0.64, 0.5, 1, 1, 6, 0.1));
//    vector<ColourRGB> tableColours(1, ColourRGB(1.0, 1.0, 1.0));
//    TriangleMesh *top = new TriangleMesh("OBJ/top.obj", tableMaterials, tableColours);
//    top->scale(4., 4., 4.);
//    top->rotateX(-PI/25);
//    top->translate(0.0, -0.452, -1.25);
//    top->loadTextureForMesh(0, "OBJ/green.ppm");
//    objects.push_front(top);
//    
//    // Insert a single point light source.
//    PointLightSource *light = new PointLightSource(ColourRGB(0.8, 0.8, 0.8),       // original
//                                                   Point3D(-12, 9, -16, false));
//    lights.push_front(light);
////    Point3D lightPosition(-12, 9, -16, false);
////    Point3D lightDirection = (Point3D(0, -0.452, -1.25, false) - lightPosition).normalized();
////    AreaLightElement::addAreaLight(2.5, 2.5, lightDirection, Point3D(0, 0, 1, true).crossUnit(lightDirection),
////                                   lightPosition, 8, 8,
////                                   ColourRGB(0.8, 0.8, 0.8), lights);
//}
//
//void buildBlurScene() {
////    vector<Material> materials(1, Material(0.05, 0.4, 0.0, 0.0, 0.0, 1.3, 6, 0.05));
////    vector<ColourRGB> colours(1, ColourRGB(0.51, 0.588, 0.333));
////    TriangleMesh *obj = new TriangleMesh("OBJ/teapot.obj", materials, colours);
////    objects.push_front(obj);
//    
//    Sphere *obj = new Sphere(Material::FrostedGlass(), ColourRGB(1.0, 1.0, 1.0));
//    objects.push_front(obj);
//    
//    PointLightSource *light = new PointLightSource(ColourRGB(0.95, 0.95, 0.95),       // original
//                                                   Point3D(0.0, 15.5, -5.5, false));
//    lights.push_front(light);
//}
//
//void buildScene(void)
//{
//    // Sets up all objects in the scene. This involves creating each object,
//    // defining the transformations needed to shape and position it as
//    // desired, specifying the reflectance properties (material and colours)
//    // and setting up textures where needed.
//    // Light sources must be defined, positioned, and their colour defined.
//    Object3D *obj = new Plane(Material(0.05, 0.75, 0.05, 0.05, 1, 1, 2, 0.3),  // original
//                              ColourRGB(0.55, 0.8, 0.75));
//    obj->scale(12, 12, 2);
//    obj->rotateZ(PI/1.20);
//    obj->rotateX(PI/2.25);
//    obj->translate(0, -3, 10);
//    // and store the inverse
//    // transform for this object!
////    obj->loadTexture("Textures/greyscale_natural_grunge2.ppm");
//    objects.push_front(obj);    // Insert into object list
//    
//    obj = new Sphere(Material(0.05, 0.95, 0.35, 0.35, 1, 1, 6, 0.3),
//                     ColourRGB(1.0, 0.25, 0.25));
//    obj->scale(0.75, 0.5, 1.5);
//    obj->rotateY(PI/2.0);
//    obj->translate(-1.45, 1.1, 3.5);
////    obj->loadTexture("Textures/webtreats_stone_5.ppm");
//    objects.push_front(obj);
//    
//    obj = new Sphere(Material(0.05, 0.95, 0.95, 0.75, 1, 1, 6, 0.3),
//                     ColourRGB(0.75, 0.95, 0.55));
//    obj->scale(0.5, 2.0, 1.0);
//    obj->rotateZ(PI/1.5);
//    obj->translate(1.75, 1.25, 5.0);
////    obj->loadTexture("Textures/webtreats_stone_4.ppm");
//    objects.push_front(obj);
//    
//    // Test OBJ
//    //    obj = new TriangleMesh("OBJ/table.obj",Material(0.05, 0.95, 0.35, 0.35, 1, 1, 6, 0.3),
//    //                                     ColourRGB(1.0, 0.25, 0.25));
//    //    //obj->scale(1.5, 1.5, 1.5);
//    //    //obj->translate(1, 0, 3.5);
//    //    obj->updateInverse();
//    //    objects.push_front(obj);
//    
//    // Insert a single point light source.
//    PointLightSource *light = new PointLightSource(ColourRGB(0.95, 0.95, 0.95),       // original
//                                                   Point3D(0.0, 15.5, -5.5, false));
//    lights.push_front(light);
//    AreaLightElement::addAreaLight(5, 5, Point3D(0, -1, 0, true), Point3D(1, 0, 0, true),
//                                   Point3D(0.0, 15.5, -5.5, false), 8, 8,
//                                   ColourRGB(0.95, 0.95, 0.95), lights);
//}
//
//int main(int argc, char *argv[])
//{
//    // Main function for the raytracer. Parses input parameters,
//    // sets up the initial blank image, and calls the functions
//    // that set up the scene and do the raytracing.
//    Image *im;          // Will hold the raytraced image
//    int sx;             // Size of the raytraced image
//    int antialiasing;	// Flag to determine whether antialiaing is enabled or disabled
//    char output_name[1024];	// Name of the output file for the raytraced .ppm image
//    Point3D e;          // Camera view parameters 'e', 'g', and 'up'
//    Point3D g;
//    Point3D up;
//    ColourRGB background(0.0, 0.0, 0.0);// Background colour
//    RayTracer rayTracer;    // The ray tracer
//    
//    // Parallization parameters
//    vector<int> bounds;
//    int firstRow, lastRow;
//    int firstCol, lastCol;
//    
//    if (argc<9)
//    {
//        fprintf(stderr,"RayTracer: Can not parse input parameters\n");
//        fprintf(stderr,"USAGE: RayTracer size rec_depth antialias output_name\n");
//        fprintf(stderr,"   size = Image size (both along x and y)\n");
//        fprintf(stderr,"   rec_depth = Recursion depth\n");
//        fprintf(stderr,"   antialias = A single digit, 0 disables antialiasing. Anything else enables antialiasing\n");
//        fprintf(stderr,"   output_name = Name of the output file, e.g. MyRender.ppm\n");
//        fprintf(stderr,"   parallization_params = 4 params for the bounds of pixels we are generating\n");
//        exit(0);
//    }
//    sx=atoi(argv[1]);
//    MAX_DEPTH=atoi(argv[2]);
//    if (atoi(argv[3])==0) antialiasing=0; else antialiasing=1;
//    strcpy(&output_name[0],argv[4]);
//    
//    bounds.push_back(atoi(argv[5]));
//    bounds.push_back(atoi(argv[6]));
//    bounds.push_back(atoi(argv[7]));
//    bounds.push_back(atoi(argv[8]));
//    
//    fprintf(stderr,"Rendering image at %d x %d\n",sx,sx);
//    fprintf(stderr,"Recursion depth = %d\n",MAX_DEPTH);
//    if (!antialiasing) fprintf(stderr,"Antialising is off\n");
//    else fprintf(stderr,"Antialising is on\n");
//    fprintf(stderr,"Output file name: %s\n",output_name);
//    
//    // Allocate memory for the new image
//    im = new Image(sx, sx);
//    
////    buildScene();       // Create a scene. This defines all the objects in the world of the raytracer
//    buildStillLife();
////    buildBlurScene();
//    
//    // Camera center is at (0,0,-3)
//    e = Point3D(0.0, 0.0, -3.0, false);
//    
//    // To define the gaze vector, we choose a point 'pc' in the scene that
//    // the camera is looking at, and do the vector subtraction pc-e.
//    // Here we set up the camera to be looking at the origin
//    g = Point3D(0.0, 0.0, 0.0, false) - e;
//    
//    // Define the 'up' vector to be the Y axis
//    up = Point3D(0, 1, 0, true);
//    
//    // Set up view with given the above vectors, a 4x4 window,
//    // and a focal length of -1 (why? where is the image plane?)
//    // Note that the top-left corner of the window is at (2, 2)
//    // in camera coordinates.
//    Camera cam(e, g, up, -3, 4);
//    
//    // Setup the skybox
//    Skybox *skybox = NULL;
//    skybox = new Skybox("Skyboxes/lagoon_lf.ppm", "Skyboxes/lagoon_rt.ppm",
//                        "Skyboxes/lagoon_dn.ppm", "Skyboxes/lagoon_up.ppm",
//                        "Skyboxes/lagoon_bk.ppm", "Skyboxes/lagoon_ft.ppm");
//    
//    fprintf(stderr,"View parameters:\n");
//    fprintf(stderr,"Width=%f, f=%f\n", cam.wsize,cam.f);
//    fprintf(stderr,"Camera to world conversion matrix (make sure it makes sense!):\n");
//    cam.cameraToWorld.printTransform3D();
//    fprintf(stderr,"World to camera conversion matrix\n");
//    cam.worldToCamera.printTransform3D();
//    fprintf(stderr,"\n");
//    
//    // Render the image with ray tracing
//    rayTracer.skybox = skybox;
//    rayTracer.maxDepth = MAX_DEPTH;
//    rayTracer.antialiasingEnabled = antialiasing;
//    rayTracer.superSamplingResolution = 5;
//    rayTracer.glossyreflEnabled = true;
//    rayTracer.refractionEnabled = true;
//    rayTracer.blurEnabled = true;
//    rayTracer.renderImage(cam, objects, lights, im, output_name, bounds);
//    
//    // Exit section. Clean up and return.
//    delete im;
//    if (skybox != NULL) {
//        delete skybox;
//    }
//    while (!objects.empty()) {
//        delete objects.front();
//        objects.pop_front();
//    }
//    while (!lights.empty()) {
//        delete lights.front();
//        lights.pop_front();
//    }
//    return 0;
//}
