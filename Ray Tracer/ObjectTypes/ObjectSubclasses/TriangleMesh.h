#ifndef TriangleMesh_h
#define TriangleMesh_h

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

	int max_x, min_x, max_y, min_y, max_z, min_z; //Coord bounds of bounding box;

protected:
	ColourRGB colourAtLocalPoint(const Point3D &up) const;

public:
	TriangleMesh(const Material &material, const ColourRGB &colour);
	TriangleMesh(const string filename, const Material &material, const ColourRGB &colour);

	bool loadOBJ(const string path);

	Intersection intersect(const Ray3D &ray);
};

#endif
