#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include <iostream>

class Texture
{
public:
    GLuint ID;

    GLuint Width, Height, Channel_n;

    GLuint Internal_Format;
    GLuint Image_Format;

    GLuint Wrap_S;
    GLuint Wrap_T;
    GLuint Filter_Min;
    GLuint Filter_Max;

    Texture();

    void Generate(GLuint width, GLuint height, GLuint ch_n, int num, bool repeated, unsigned char *data);
    void Bind() const;
    int NextFrame();

private:
    int texture_index;
    int texture_array_length;
    bool repeated;
};

#endif