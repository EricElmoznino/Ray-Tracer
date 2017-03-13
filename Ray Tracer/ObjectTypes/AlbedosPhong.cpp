#include "AlbedosPhong.h"

AlbedosPhong::AlbedosPhong(double ambient, double diffuse, double specular, double global) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->global = global;
}
