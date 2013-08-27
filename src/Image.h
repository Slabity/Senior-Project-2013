#ifndef IMAGE_H
#define IMAGE_H

#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_opengl.h>

#include "Vector2d.h"

class Image {
public:
    //Create the image with a filename.
    Image(char*);
    ~Image();

    //Draw the image onto the sceen.
    void drawImage(Vector2d);

    //Return the sizes of the image itself.
    unsigned int getWidth();
    unsigned int getHeight();
private:
    //Hold the surface into memory.
    GLuint m_TextureID;
    int m_Width;
    int m_Height;
};

#endif
