#ifndef Material_h
#define Material_h

#include <stdio.h>

class Material {
public:
    double ambient;
    double diffuse;
    double specular;
    double global;
    
    double alpha;   // Opacity - if less than 1 this is a semi transparent object
    // and refraction rays should be implemented
    double refractionIndex;
    double shinyness;   // Exponent for phong specular component
    
    Material(double ambient, double diffuse, double specular, double global,
             double alpha, double refractionIndex, double shinyness);
    Material(){}
};

#endif
