# Ray-Tracer
A graphics ray tracer that can render a variety of basic shapes as well as arbitrary meshes. Features include anti-aliasing, soft shadows, glossy reflections, refraction, texture mapping, arbitrary mesh rendering, customizable material properties, skyboxes, and bounding-box hierarchies, among other things.

Some samples of generated images are shown in the GeneratedImages folder, with ChessScene.ppm in particular being the best example.

Important implementation files/folders (all with reference to /RayTracer/):
- RayTracer.cpp:
The ray tracer entry point and various rendering methods.
- ObjectTypes/:
Classes for properties relevant to renderable objects, such as material and colour. Also contains the abstract object class (Object3D) and all of its subclasses (ObjectSubclasses/).
- GeometricTypes/:
The mathematical types, such as affine transforms and points.
- Lights/:
The lighting classes.
- Camera.cpp:
Describes a camera's position, orientation, and focal properties.
- main.cpp:
An example program that uses the ray tracer.

Assets:
- OBJ/:
Some mesh objects.
- Skyboxes/:
Images for skyboxes (6 for each, corresponding to the 6 sides of a dice).
- Textures/:
Sample images that can be mapped as textures to objects.

Machine learning side project:
The ML folder contains code that generates random scenes, capturing two images for each with the camera slightly perturbed in orientation and position. The purpose of this is to generate data for a spatial awareness AI project that I worked on described here  https://github.com/EricElmoznino/Attitude_4

Compilation/Runing:
- If you have a mac, you can try loading the XCode project and running it.
- Take a look at the compile*.sh and run*.sh scripts. You may have to make some changes.
