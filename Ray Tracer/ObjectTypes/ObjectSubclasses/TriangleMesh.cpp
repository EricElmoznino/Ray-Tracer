#include "TriangleMesh.h"

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
	}
	else{
		printf("Error: OBJ NOT LOADED!\n");
	}
	Object3D::isLight = false;
}

ColourRGB TriangleMesh::colourAtLocalPoint(const Point3D &p) const {
	return colour;
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
		file << "Bounds of bounding box: X: [" << curMesh.min_x << " " << curMesh.max_x << "] Y: [" << curMesh.min_y << " " << curMesh.max_y << "]\n";

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
	Point3D normal = Point3D(0, -1, 0, true);

	//Check if intersects within plane's bounds
	if (p.x >= curMesh.min_x && p.x <= curMesh.max_x && p.y >= curMesh.min_y && p.y <= curMesh.max_y)
	{
		/*vector<double> intersection_points
		for (int j = 0; j < curMesh.Indices.size(); j += 3)
		{
			objl::Vector3 p1 = curMesh.Vertices[curMesh.Indices[j]];
			objl::Vector3 p2 = curMesh.Vertices[curMesh.Indices[j+1]];
			objl::Vector3 p3 = curMesh.Vertices[curMesh.Indices[j+2]];



		}
		for (int j = 0; j < curMesh.Vertices.size(); j++)
		{

		}
		*/
		Point3D hitNormalLocal = rayDirection.dot(normal) < 0 ? normal : -1*normal;

		intersection.none = false;
		intersection.isLight = Object3D::isLight;
		intersection.insideObject = false;
		intersection.lambda = t;
		intersection.point = ray.rayPosition(t);
		intersection.normal = (invTransform.transpose() * hitNormalLocal).normalized();
		intersection.material = material;
		intersection.colour = colourAtLocalPoint(p);
		intersection.obj = this;

		return intersection;
	}

	intersection.none = true;
	return intersection;
}

//double TriangleMesh::findIntersectionPoint(Point3D origin, Point3D direction, Point3D )
