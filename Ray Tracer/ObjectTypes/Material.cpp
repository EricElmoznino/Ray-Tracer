#include "Material.h"

Material::Material(double ambient, double diffuse, double specular, double global) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->global = global;
}
