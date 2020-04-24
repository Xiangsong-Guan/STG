#include "texture.h"

void Texture::Generate(GLuint width, GLuint height, GLuint ch_n, unsigned char *data)
{
    GLuint format;

    this->Width = width;
    this->Height = height;
    switch (ch_n)
    {
    case 1:
        format = GL_RED;
        break;
    case 2:
        format = GL_RG;
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
        break;
    default:
        std::cout << "ERROR::TEXTURE: Unsupported image format" << std::endl;
        break;
    }
    // Create Texture
    glGenTextures(1, &this->ID);
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Binds the texture as the current active GL_TEXTURE_2D texture object
void Texture::Bind(int unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}
