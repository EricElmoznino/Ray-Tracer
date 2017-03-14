#include "Object3D.h"

Object3D::Object3D(const AlbedosPhong &albedos, const ColourRGB &colour,
                   double alpha, double refractionIndex, double shinyness) :
albedos(albedos), colour(colour) {
    this->albedos = albedos;
    this->colour = colour;
    this->alpha = alpha;
    this->refractionIndex = refractionIndex;
    this->shinyness = shinyness;
    this->textureImage = NULL;
    this->transform = Transform3D::identity();
    this->invTransform = Transform3D::identity();
    this->bothSidesLit = false;         // default
    this->isAreaLightSource = false;    // default
}

Object3D::Object3D(const Object3D &obj) :
albedos(obj.albedos), colour(obj.colour) {
    albedos = obj.albedos;
    colour = obj.colour;
    alpha = obj.alpha;
    refractionIndex = obj.refractionIndex;
    shinyness = obj.shinyness;
    transform = obj.transform;
    invTransform = obj.invTransform;
    bothSidesLit = obj.bothSidesLit;
    isAreaLightSource = obj.isAreaLightSource;
    
    if (obj.textureImage == NULL)
        textureImage = NULL;
    else
        textureImage = new Image(*obj.textureImage);
}

Object3D::~Object3D() {
    if (textureImage != NULL)
        delete textureImage;
}

Object3D& Object3D::operator=(const Object3D &obj) {
    albedos = obj.albedos;
    colour = obj.colour;
    alpha = obj.alpha;
    refractionIndex = obj.refractionIndex;
    shinyness = obj.shinyness;
    transform = obj.transform;
    invTransform = obj.invTransform;
    bothSidesLit = obj.bothSidesLit;
    isAreaLightSource = obj.isAreaLightSource;
    
    if (textureImage != NULL && obj.textureImage != NULL)
        *textureImage = *obj.textureImage;
    else if(textureImage == NULL && obj.textureImage != NULL)
        textureImage = new Image(*obj.textureImage);
    else if(textureImage != NULL && obj.textureImage == NULL) {
        delete textureImage;
        textureImage = NULL;
    }
    // else both NULL, nothing to do
    
    return (*this);
}

void Object3D::rotateX(double theta) {
    transform = Transform3D::rotatedX(theta) * transform;
}

void Object3D::rotateY(double theta) {
    transform = Transform3D::rotatedY(theta) * transform;
}

void Object3D::rotateZ(double theta) {
    transform = Transform3D::rotatedZ(theta) * transform;
}

void Object3D::translate(double x, double y, double z) {
    transform = Transform3D::translated(x, y, z) * transform;
}

void Object3D::scale(double x, double y, double z) {
    transform = Transform3D::scaled(x, y, z) * transform;
}

void Object3D::updateInverse() {
    invTransform = transform.inverse();
}

// Load a texture image from file and assign it to the
// specified object
void Object3D::loadTexture(const char *filename) {
    if (textureImage != NULL)   // Already had a texture loaded
        delete textureImage;
    
    textureImage = Image::readPPMimage(filename);
}
