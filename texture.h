#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include <iostream>

class Texture
{
public:
    GLuint ID;
    GLuint Width, Height;

    Texture() = default;
    Texture(const Texture &) = default;
    Texture(Texture &&) = default;
    Texture &operator=(const Texture &) = default;
    Texture &operator=(Texture &&) = default;
    ~Texture() = default;

    void Generate(GLuint width, GLuint height, GLuint ch_n, unsigned char *data);
    void Bind(int unit = 0) const;
};

#endif