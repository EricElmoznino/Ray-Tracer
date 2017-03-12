#ifndef Image_h
#define Image_h

#include <stdio.h>

class Image {
public:
    void *rgbImageData;
    int sx;
    int sy;
    
    Image();    // Note: this constructor does not allocate space for the image data
    Image(int sx, int sy);
    Image(const Image &im);
    ~Image();
    
    Image& operator=(const Image &im);
    
    static Image* readPPMimage(const char *filename);
    
    // Writes out a .ppm file from the image data contained in 'im'.
    // Note that Windows typically doesn't know how to open .ppm
    // images. Use Gimp or any other seious image processing
    // software to display .ppm images.
    // Also, note that because of Windows file format management,
    // you may have to modify this file to get image output on
    // Windows machines to work properly.
    //
    // Assumes a 24 bit per pixel image stored as unsigned chars
    //

    void outputImage(const char *filename);
};

#endif
