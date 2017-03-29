#include "Material.h"

Material::Material(double ambient, double diffuse, double specular, double global,
                   double alpha, double refractionIndex, double shinyness, double roughness) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->global = global;
    this->alpha = alpha;
    this->refractionIndex = refractionIndex;
    this->shinyness = shinyness;
    this->roughness = roughness;
}
