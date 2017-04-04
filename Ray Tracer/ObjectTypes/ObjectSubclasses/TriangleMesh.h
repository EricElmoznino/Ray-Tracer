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
	objl::Mesh curMesh;
    vector<Transform3D> triangleTransforms;
    
    void normalizeVertices(void);
    bool intersectBoundingBox(const Point3D &origin, const Point3D &direction);
    double findIntersectionParams(Point3D &origin, Point3D &direction,
                                  int triangleFace, double *u, double *v);
    Point3D findNormal(int faceIndex, double u, double v);
	ColourRGB colourAtTrianglePoint(int faceIndex, double u, double v) const;

public:
	TriangleMesh(const Material &material, const ColourRGB &colour);
	TriangleMesh(const string filename, const Material &material, const ColourRGB &colour);

	bool loadOBJ(const string path);

	Intersection intersect(const Ray3D &ray);
};

#endif
