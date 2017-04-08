#ifndef TriangleMesh_h
#define TriangleMesh_h

#include "OBJ_Loader.h"

#include "../Object3D.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <stdio.h>

using namespace std;

class TriangleMesh : public Object3D{
	/*
	 * Input: str path to .obj file
	 */
    vector<vector<Transform3D>> triangleTransforms;
    
    bool isLoaded = false;
    vector<objl::Mesh> meshes;
    vector<ColourRGB> colours;
    vector<Material> materials;
    vector<Image> textureImages;
    
    void normalizeVertices(void);
    bool intersectBoundingBox(const Point3D &origin, const Point3D &direction);
    double findIntersectionParams(Point3D &origin, Point3D &direction,
                                  int mesh, int triangleFace, double *u, double *v);
    Point3D findNormal(int mesh, int faceIndex, double u, double v);
	ColourRGB colourAtTrianglePoint(int mesh, int faceIndex, double u, double v) const;

public:
	TriangleMesh(const vector<Material> &materials, const vector<ColourRGB> &colours);
	TriangleMesh(const string filename, const vector<Material> &materials, const vector<ColourRGB> &colours);
    
    void loadTextureForMesh(int i, const char *filename);

    bool loadOBJ(const string path);

	Intersection intersect(const Ray3D &ray);
    
    bool doesIntersect(const Ray3D &ray);
};

#endif
