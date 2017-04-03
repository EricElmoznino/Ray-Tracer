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

protected:
	ColourRGB colourAtLocalPoint(const Point3D &up) const;

public:
	TriangleMesh(const Material &material, const ColourRGB &colour);
	TriangleMesh(const string filename, const Material &material, const ColourRGB &colour);

	bool loadOBJ(const string path);

	Intersection intersect(const Ray3D &ray);
	double findIntersectionPoint(Point3D &origin, Point3D &direction, Point3D &p1, Point3D &p2, Point3D &p3);

};

#endif
