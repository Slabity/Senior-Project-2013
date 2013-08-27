#include "Image.h"

#include <stdlib.h>
#include <stdio.h>

#include "Application.h"

//Set the surface to NULL.
Image::Image(char* filename)
{
    //Create a temporary surface.
    SDL_Surface* image = IMG_Load(filename);

    //Error check the image.
    if(image == NULL) {
       fprintf(stderr, "Unable to load image: %s\n", filename);
       exit(101);
    }

    //Set the width and height to the measure of the file.
    m_Width  = image->w;
    m_Height = image->h;

    //Check that the image's width is a power of 2
    if ((image->w & (image->w - 1)) != 0 ) {
        fprintf(stderr, "Warning: %s is not of proper width\n", filename);
    }

    //Also check if the height is a power of 2
    if ((image->h & (image->h - 1)) != 0 ) {
        fprintf(stderr, "Warning: %s is not of proper height\n", filename);
    }

    //Get the number of channels in the image.
    GLint colors = image->format->BytesPerPixel;
    GLenum format;

    if (colors == 4) { //All channels, including Alpha

        //Check if the format is RGBA or BGRA.
        if (image->format->Rmask == 0x000000ff) {
            format = GL_RGBA;
        } else {
            format = GL_BGRA;
        }

    } else if (colors == 3) { //No Alpha channel

        //Check if format is RGB or BGR.
        if (image->format->Rmask == 0x000000ff) {
            format = GL_RGB;
        } else {
            format = GL_BGR;
        }

    } else { //Crash if we are unable to decipher color type.
        fprintf(stderr, "Unable to decipher color type.\n");
        exit(102);
    }

    //Generate the texture and bind the ID.
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Generate the OpenGL image from the SDL_Surface
    glTexImage2D(GL_TEXTURE_2D, 0, colors, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, image->pixels);

    //Delete the temporary SDL_Surface to prevent a memory leak.
    SDL_FreeSurface(image);
}

Image::~Image() {
    //Delete the texture from memory.
    glDeleteTextures(1, &m_TextureID);
}

//Draw the image on the window.
void Image::drawImage(Vector2d pos)
{
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    glBegin(GL_LINES);
        //glTexCoord2f(0.0f, 0.0f);
            glVertex3f(pos.x, pos.y, 0.0f);
        //glTexCoord2f(1.0f, 0.0f);
            glVertex3f(pos.x + m_Width, pos.y, 0.0f);
        //glTexCoord2f(1.0f, 1.0f);
            glVertex3f(pos.x + m_Width, pos.y + m_Height, 0.0f);
        //glTexCoord2f(0.0f, 1.0f);
            glVertex3f(pos.x, pos.y + m_Height, 0.0f);
    glEnd();
}

//Return the width of the image.
unsigned int Image::getWidth()
{
    return m_Width;
}

//Return the height of the image.
unsigned int Image::getHeight()
{
    return m_Height;
}
