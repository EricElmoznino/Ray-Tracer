#include "Object3D.h"

bool Object3D::isLightSource() {
    return isLight;
}

Object3D::Object3D(const Material &material, const ColourRGB &colour) :
material(material), colour(colour) {
    this->material = material;
    this->colour = colour;
    this->textureImage = NULL;
    this->transform = Transform3D::identity();
    this->invTransform = Transform3D::identity();
    this->bothSidesLit = false;         // default
    this->isLight = false;              // default
}

Object3D::Object3D(const Object3D &obj) :
material(obj.material), colour(obj.colour) {
    material = obj.material;
    colour = obj.colour;
    transform = obj.transform;
    invTransform = obj.invTransform;
    bothSidesLit = obj.bothSidesLit;
    isLight = obj.isLight;
    
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
    material = obj.material;
    colour = obj.colour;
    transform = obj.transform;
    invTransform = obj.invTransform;
    bothSidesLit = obj.bothSidesLit;
    isLight = obj.isLight;
    
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

Point3D Object3D::originInWorld() const {
    return transform.translationComponent();
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
