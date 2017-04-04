#include "TriangleMesh.h"
#include <vector>
#include <algorithm>
#include <string>

TriangleMesh::TriangleMesh(const Material &material, const ColourRGB &colour) :
Object3D::Object3D(material, colour){
	Object3D::isLight = false;
}

TriangleMesh::TriangleMesh(const string filename, const Material &material, const ColourRGB &colour) :
Object3D::Object3D(material, colour){
	bool isLoaded = loadOBJ(filename);
	if (isLoaded)
	{
		printf("OBJ successfully loaded!\n");
		//Material prop from loaded mesh:
		//Ambient Color
		/*double Ka = Point3D(curMesh.MeshMaterial.Ka, true).average();
		printf("Ka: %f\n", Ka);
		//Diffuse Color
		double Kd = Point3D(curMesh.MeshMaterial.Kd, true).average();
		printf("Kd: %f\n", Kd);

		//Specular Color
		double Ks = Point3D(curMesh.MeshMaterial.Ks, true).average();
		printf("Ks: %f\n", Ks);

		//Exponent for phong specular component
		double shinyness = curMesh.MeshMaterial.Ns;
		printf("shinyness: %f\n", shinyness);

		//Dissolve? -> Opacity
		//double opacity = curMesh.MeshMaterial.d;
		//printf("opacity: %f\n", opacity);
		Material fromMesh(Ka, Kd, Ks, material.global, material.opacity, material.refractionIndex,
				shinyness, material.roughness);
		Object3D::material = fromMesh;
		*/
		//Update texture - if given
		if (!curMesh.MeshMaterial.map_Kd.empty())
		{
			string name = curMesh.MeshMaterial.map_Kd.substr(0, curMesh.MeshMaterial.map_Kd.find("."));
			string start("OBJ/");
			string end(".ppm");
			start.append(name);
			start.append(end);
			printf("NAME: %s\n", start.c_str());
			Object3D::loadTexture(start.c_str());
		}
	}
	else{
		printf("Error: OBJ NOT LOADED!\n");
		Object3D::material = material;
	}
	Object3D::material = material;

	Object3D::colour = colour;
	Object3D::isLight = false;
}

ColourRGB TriangleMesh::colourAtLocalPoint(const Point3D &p) const {
    //if (textureImage.rgbImageData == NULL) {
        return colour;
    //}
}

bool TriangleMesh::loadOBJ(const string path)
{
	//Initialize loader
	objl::Loader Loader;

	//Load obj
	bool loadout = Loader.LoadFile(path);

	if (loadout)
	{
	// Create/Open e1Out.txt
		std::ofstream file("e1Out.txt");


		// Copy one of the loaded meshes to be our current mesh
		curMesh = Loader.LoadedMeshes[0];

		normalizeVertices();
		// Print Mesh Name
		file << "Mesh " << 0 << ": " << curMesh.MeshName << "\n";

		// Print Vertices
		file << "Vertices:\n";

		// Go through each vertex and print its number,
		//  position, normal, and texture coordinate
		for (int j = 0; j < curMesh.Vertices.size(); j++)
		{
			file << "V" << j << ": " <<
				"P(" << curMesh.Vertices[j].Position.X << ", " << curMesh.Vertices[j].Position.Y << ", " << curMesh.Vertices[j].Position.Z << ") " <<
				"N(" << curMesh.Vertices[j].Normal.X << ", " << curMesh.Vertices[j].Normal.Y << ", " << curMesh.Vertices[j].Normal.Z << ") " <<
				"TC(" << curMesh.Vertices[j].TextureCoordinate.X << ", " << curMesh.Vertices[j].TextureCoordinate.Y << ")\n";
		}

		// Print bounds of box
		file << "Bounds of bounding box: X: [" << curMesh.min_x << " " << curMesh.max_x << "] Y: [" << curMesh.min_y << " " << curMesh.max_y << "] Z: [" << curMesh.min_z << " " << curMesh.max_z << "]\n";

		// Print Indices
		file << "Indices:\n";

		// Go through every 3rd index and print the
		//	triangle that these indices represent
		for (int j = 0; j < curMesh.Indices.size(); j += 3)
		{
			file << "T" << j / 3 << ": " << curMesh.Indices[j] << ", " << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2] << "\n";
		}

		// Print Material
		file << "Material: " << curMesh.MeshMaterial.name << "\n";
		file << "Ambient Color: " << curMesh.MeshMaterial.Ka.X << ", " << curMesh.MeshMaterial.Ka.Y << ", " << curMesh.MeshMaterial.Ka.Z << "\n";
		file << "Diffuse Color: " << curMesh.MeshMaterial.Kd.X << ", " << curMesh.MeshMaterial.Kd.Y << ", " << curMesh.MeshMaterial.Kd.Z << "\n";
		file << "Specular Color: " << curMesh.MeshMaterial.Ks.X << ", " << curMesh.MeshMaterial.Ks.Y << ", " << curMesh.MeshMaterial.Ks.Z << "\n";
		file << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
		file << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
		file << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
		file << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
		file << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
		file << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Kd << "\n";
		file << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks << "\n";
		file << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
		file << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";

		// Leave a space to separate from the next mesh
		file << "\n";

		// Close File
		file.close();
	}
	// If not output an error
	else
	{
		// Create/Open e1Out.txt
		std::ofstream file("e1Out.txt");

		// Output Error
		file << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";

		// Close File
		file.close();
	}
	return loadout;
}

Intersection TriangleMesh::intersect(const Ray3D &ray) {
	Intersection intersection;

    // Acquire ray in local coordinates
    Point3D rayOrigin = invTransform*ray.origin; //e
    Point3D rayDirection = invTransform*ray.direction; //d

    double t = -rayOrigin.z/rayDirection.z;

	//Invalid intersection - behind camera
	if (t < 0 || rayDirection.z == 0)
	{
		intersection.none = true;
		return intersection;
	}

	//Intersection point
	Point3D p = rayOrigin + t*rayDirection;

	//Check if intersects within sphere's bounds
	if (intersectBoundingBox(ray))
	{
		vector<double> intersection_points;

		for (int j = 0; j < curMesh.Indices.size(); j += 3)
		{
			//printf("Vert at Index: %i\n", j);
			Point3D p1 = Point3D(curMesh.Vertices[curMesh.Indices[j]].Position, false);
			//p1.printPoint3D();
			//printf("Vert at Index: %i\n", j+1);
			Point3D p2 = Point3D(curMesh.Vertices[curMesh.Indices[j+1]].Position, false);
			//p2.printPoint3D();
			//printf("Vert at Index: %i\n", j+2);
			Point3D p3 = Point3D(curMesh.Vertices[curMesh.Indices[j+2]].Position, false);
			//p3.printPoint3D();

			double point = findIntersectionPoint(rayOrigin, rayDirection, p1, p2, p3);
			//printf("Intersection point %f\n", point);
			intersection_points.push_back(point);
		}

		vector<double>::iterator it = min_element(intersection_points.begin(), intersection_points.end());

		if (*it == DBL_MAX)
		{
			intersection.none = true;
			return intersection;
		}

		//printf("INTERSECTION - MIN: %f\n", *it);
		int index = distance(intersection_points.begin(), it);

		Point3D normal = findNormal(index);

		//Point3D normal = Point3D(curMesh.Vertices[index].Normal, true);
		Point3D hitPointLocal = rayOrigin + (*it)*rayDirection;
		Point3D hitNormalLocal = rayDirection.dot(normal) < 0 ? normal : -1*normal;

		intersection.none = false;
		intersection.isLight = Object3D::isLight;
		intersection.insideObject = false;
		intersection.lambda = *it;
		intersection.point = ray.rayPosition(*it);
		intersection.normal = (invTransform.transpose() * hitNormalLocal).normalized();
		intersection.material = material;
		intersection.colour = colourAtLocalPoint(hitPointLocal);
		intersection.obj = this;

		return intersection;
	}

	intersection.none = true;
	return intersection;
}

Point3D TriangleMesh::findNormal(int faceIndex) {
	//Find normal by averaging vertices of the corresponding face
	Point3D vertexIndices = Point3D(curMesh.Indices[faceIndex], curMesh.Indices[faceIndex+1], curMesh.Indices[faceIndex+2], false);
	Point3D n1 = Point3D(curMesh.Vertices[faceIndex].Normal, true);
	Point3D n2 = Point3D(curMesh.Vertices[faceIndex+1].Normal, true);
	Point3D n3 = Point3D(curMesh.Vertices[faceIndex+2].Normal, true);
	return Point3D(n1, n2, n3, true);
}

void TriangleMesh::normalizeVertices(void) {
	//Normalize vertex coords to between -0.5 to 0.5
	for (int j = 0; j < curMesh.Vertices.size(); j++)
	{
		double x = ((curMesh.Vertices[j].Position.X - curMesh.min_x)/(curMesh.max_x - curMesh.min_x)) - 0.5;
		curMesh.Vertices[j].Position.X = x;

		double y = ((curMesh.Vertices[j].Position.Y - curMesh.min_y)/(curMesh.max_y - curMesh.min_y)) - 0.5;
		curMesh.Vertices[j].Position.Y = y;

		double z = ((curMesh.Vertices[j].Position.Z - curMesh.min_z)/(curMesh.max_z - curMesh.min_z)) - 0.5;
		curMesh.Vertices[j].Position.Z = z;
	}
}

bool TriangleMesh::intersectBoundingBox(const Ray3D &ray){
	/*
	 * Check if ray intersects with Bounding box with bounds
	 * -.5 to .5
	 */
    // Acquire ray in local coordinates
    Point3D rayOrigin = invTransform*ray.origin; //e
    Point3D rayDirection = invTransform*ray.direction; //d

    Point3D invRayDirection = Point3D(1/rayDirection.x, 1/rayDirection.y, 1/rayDirection.z, true);

    int sign [3];
    sign[0] = (invRayDirection.x < 0);
    sign[1] = (invRayDirection.y < 0);
    sign[2] = (invRayDirection.z < 0);

    Point3D bounds [2];
    bounds[0] = Point3D(-.5, -.5, -.5, false);
    bounds[1] = Point3D(.5, .5, .5, false);

    double xmin, xmax, ymin, ymax, zmin, zmax;

    xmin = (bounds[sign[0]].x - rayOrigin.x)*invRayDirection.x;
    xmax = (bounds[1-sign[0]].x - rayOrigin.x)*invRayDirection.x;
    ymin = (bounds[sign[1]].y - rayOrigin.y)*invRayDirection.y;
    ymax = (bounds[1-sign[1]].y - rayOrigin.y)*invRayDirection.y;

    if ((xmin > ymax) || (ymin > xmax))
    {
    	return false;
    }

    if (ymin > xmin) xmin = ymin;
    if (ymax < xmax) xmax = ymax;

    zmin = (bounds[sign[2]].z - rayOrigin.z)*invRayDirection.z;
    zmax = (bounds[1-sign[2]].z - rayOrigin.z)*invRayDirection.z;

    if ((xmin > zmax) || (zmin > xmax))
    {
    	return false;
    }

    if (zmin > xmin) xmin = zmin;
    if (zmax < xmax) xmax = zmax;

    double t = xmin;

    if (t < 0) {
    	t = xmax;
    	if (t < 0) return false;
    }
    return true;
}

double TriangleMesh::findIntersectionPoint(Point3D &origin, Point3D &direction, Point3D &p1, Point3D &p2, Point3D &p3) {

    //For triangle p1, p2, p3 in plane
    Point3D ab = p1 - p3;
    Point3D ac = p1 - p2;
    Point3D ae = p1 - origin;
    Point3D h(0.0, 0.0, 0.0, false);

    Transform3D A(ab, ac, direction, h);
    A = A.inverse();                        // TO DO: A is singular sometimes and this is causing errors in those small cases

    //a.x = beta1, a.y = gamma1, a.z = t1 (a solution!)
    Point3D a = A*(ae);

    // If either lambda is negative, the plane is behind us (or we are in it)
    // and we don't want to render it. The case where we are in it might be
    // debatable as to whether or not we want to render, but if we change our
    // mind latter it's an easy fix.
    if (a.z < 0.0)
    {
        return DBL_MAX;
    }

    //Verify if the solution is inside the respective triangle
    bool inA = (a.x > 0.0 && a.y > 0.0 && a.x + a.y < 1.0);

    if (inA)
    {
        return a.z;
    }
    return DBL_MAX;
}
