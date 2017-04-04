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
    
    // Compute the inverse transforms
    for (int i = 0; i < curMesh.Indices.size(); i += 3) {
        Point3D p1(curMesh.Vertices[curMesh.Indices[i]].Position, false);
        Point3D p2(curMesh.Vertices[curMesh.Indices[i+1]].Position, false);
        Point3D p3(curMesh.Vertices[curMesh.Indices[i+2]].Position, false);
        
        Point3D ab = p2 - p1;
        Point3D ac = p3 - p1;
        Point3D n = ab.crossUnit(ac);
        
        triangleTransforms.push_back(Transform3D(ab, ac, n, p1).inverse());
    }
    
	return loadout;
}

Intersection TriangleMesh::intersect(const Ray3D &ray) {
	Intersection intersection;

    // Acquire ray in local coordinates
    Point3D rayOrigin = invTransform*ray.origin; //e
    Point3D rayDirection = invTransform*ray.direction; //d
    
	//Check if intersects within sphere's bounds
	if (intersectBoundingBox(ray))
	{
        double closestLambda = DBL_MAX;
        int closestTriangleFace = 0;
		for (int j = 0; j < curMesh.Indices.size(); j += 3)
		{
			double lambda = findIntersectionPoint(rayOrigin, rayDirection, j);
            if (lambda < closestLambda) {
                closestLambda = lambda;
                closestTriangleFace = j/3;
            }
		}

		if (closestLambda == DBL_MAX)
		{
			intersection.none = true;
			return intersection;
		}

		Point3D normal = findNormal(closestTriangleFace);

		//Point3D normal = Point3D(curMesh.Vertices[index].Normal, true);
		Point3D hitPointLocal = rayOrigin + (closestLambda)*rayDirection;
		Point3D hitNormalLocal = rayDirection.dot(normal) < 0 ? normal : -1*normal;

		intersection.none = false;
		intersection.isLight = Object3D::isLight;
		intersection.insideObject = false;
		intersection.lambda = closestLambda;
		intersection.point = ray.rayPosition(closestLambda);
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

// TODO: this function can break when rayDirection has a component that is 0
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

double TriangleMesh::findIntersectionPoint(Point3D &origin, Point3D &direction, int triangleFace) {
    // Get the transform to convert a point to triangle space
    // (triangle space has basis: {AB, AC, AB.crossUnit(AC)} where
    // A, B, and C are the vertices and XY symbolizes Y-X
    Transform3D P = triangleTransforms[triangleFace/3];
    
    Point3D o = P * origin;
    Point3D d = P * direction;
    
    if (fabs(d.z) < 1e-6) return DBL_MAX;
    
    double t = -o.z / d.z;
    double u = o.x + t * d.x;
    double v = o.y + t * d.y;
    
    if (u < 0 || v < 0 || u+v > 1) return DBL_MAX;
    
    return t;
}
