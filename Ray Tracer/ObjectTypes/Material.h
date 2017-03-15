#ifndef Material_h
#define Material_h

#include <stdio.h>

class Material {
public:
    double ambient;
    double diffuse;
    double specular;
    double global;
    
    Material(double ambient, double diffuse, double specular, double global);
    Material(){}
};

#endif
