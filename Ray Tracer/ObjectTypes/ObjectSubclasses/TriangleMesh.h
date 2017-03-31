#ifndef FileObject_h
#define FileObject_h

#include "../Object3D.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

class TriangleMesh : public Object3D{
	/*
	 * Input: str path to .obj file
	 * Output: populates V, F, N, C
	 */
	vector<Point3D> V;	//matrix of vertex pos: #Vx3
	vector<vector<int>> F;	//list of face indices into vertex pos: #Fx3
	vector<Point3D> N;	//list of vertex normals: #Vx3
	vector<Point3D> C;	//list of rgb color values per vertex: #Vx3

protected:
	ColourRGB colourAtLocalPoint(const Point3D &up) const;

public:
	TriangleMesh(const Material &material, const ColourRBG &colour);
	TriangleMesh(const string filename, const Material &material, const ColourRBG &colour);

	bool loadOBJ(const string filename);

	Intersection intersect(const Ray3D &ray);
};

#endif
