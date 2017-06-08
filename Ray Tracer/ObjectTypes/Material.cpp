#include "Material.h"

Material::Material(double ambient, double diffuse, double specular, double global,
                   double opacity, double refractionIndex, double shinyness, double roughness) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->global = global;
    this->opacity = opacity;
    this->refractionIndex = refractionIndex;
    this->shinyness = shinyness;
    this->roughness = roughness;
}

Material Material::Glass() {
    return Material(0, 0, 0, 0.12, 0.0, 1.5, 6, 0);
}

Material Material::FrostedGlass() {
    Material glass = Material::Glass();
    glass.roughness = 0.04;
    glass.diffuse = 0.8;
    glass.opacity = 0.4;
    return glass;
}

Material Material::Chrome() {
    return Material(0.25, 0.1, 0.718, 0.8, 1.0, 1.0, 100.8, 0.02);
}

Material Material::Mirror() {
    return Material(0, 0, 0, 1, 1, 1, 1000, 0);
}
