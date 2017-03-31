#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(const Material &material, const ColourRGB &colour) :
Object3D::Object3D(material, colour){}

TriangleMesh::TriangleMesh(const string filename, const Material &material, const ColourRGB &colour) :
		Object3D::Object3D(material, colour){
	bool isLoaded = loadOBJ(filename);
	if (isLoaded)
	{
		printf("OBJ successfully loaded!\n");
	}
	else{
		printf("Error: OBJ NOT LOADED!\n")
	}
}

bool TriangleMesh::loadOBJ(const string filename){
	FILE * from_file = fopen(filename.c_str(), "r");
	if (NULL == from_file)
	{
		printf("Error: %s could not be opened\n", filename.c_str());
		return false;
	}

	//First Line Info:
	char header[1000];
	const string OFF("OFF");
	const string NOFF("NOFF");
	const string COFF("COFF");

	if(fscanf(from_file, "%s\n", header)!=1 || !(string(header).compare(0, OFF.length(), OFF)==0 ||
		       string(header).compare(0, COFF.length(), COFF)==0 ||
		string(header).compare(0,NOFF.length(),NOFF)==0)){
		printf("Error: first line should be OFF, NORR or COFF, not %s", header);
		fclose(from_file);
		return false;
	}
	bool hasNormals = string(header).compare(0, NOFF.length(), NOFF)==0;
	bool hasColors = string(header).compare(0, COFF.length(), COFF)==0;

	//Second Line Info: #V, #F, #E
	int num_V;
	int num_F;
	int num_E;

	char tic_tac_toe;
	char line[1000];

	bool isComments = true;

	while (isComments)	//Exit comments - get to info!
	{
		fgets(line, 1000, from_file);
		isComments = (line[0] == '#' || line[0] == '\n');
	}

	sscanf(line, "%d %d %d", &num_V, &num_F, &num_E);	//Get # V, F, E

	//Allocate space in vectors:
	V.resize(num_V);
	if (hasNormals)
	{
		N.resize(num_V);
	}
	if (hasColors)
	{
		C.resize(num_V);
	}
	F.resize(num_F);

	//Read V
	for (int i = 0; i < num_V;)
	{
		fgets(line, 1000, from_file);
		double x, y, z, nx, ny, nz;
		if(sscanf(line, "%lg %lg %lg %lg %lg %lg", &x, &y, &z, &nx, &ny, &nz)>=3)
		{
			Point3D v = Point3D(x, y, z, false);
			V[i] = v;

			if (hasNormals)
			{
				Point3D n = Point3D(nx, ny, nz, true);
				N[i] = n;
			}
			if (hasColors)
			{
				Point3D c = Point3D(nx/255.0, ny/255.0, nz/255.0, false);
				C[i] = c;
			}
			i++;
		}else if(fscanf(from_file, "%[#]", &tic_tac_toe)==1)
		{
			char comment[1000];
			fscanf(from_file, "%[^\n]", comment);
		}else
		{
			printf("Error: bad line (%d)\n", i);
			if (feof(from_file))
			{
				fclose(from_file);
				return false;
			}
		}
	}

	//Read F
	for (int i = 0; i < num_F;)
	{
		int valence;
		vector<int> face;

		if(fscanf(from_file, "%d", &valence)==1)
		{
			face.resize(3);
			for (int j = 0; j < valence; j++)
			{
				int index;
				if (j < valence - 1)
				{
					fscanf(from_file, "%d", &index);
				}else{
					fscanf(from_file, "%d%[^/n]", &index);
				}
				face[j] = index;
			}
			F[i] = face;
			i++;
		}else if(fscanf(from_file, "%[#]", &tic_tac_toe)==1)
		{
			char comment[1000];
			fscanf(from_file, "%[^/n]", comment);
		}else{
			printf("Error: bad line\n");
			fclose(from_file);
			return false;
		}
	}
	fclose(from_file);
	return true;
}
