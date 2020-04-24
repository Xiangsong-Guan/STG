#include "texture.h"

Texture::Texture() : ID(0), Width(0), Height(0), Channel_n(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_CLAMP_TO_EDGE), Wrap_T(GL_CLAMP_TO_EDGE), Filter_Min(GL_NEAREST), Filter_Max(GL_NEAREST), texture_array_length(0), texture_index(0), repeated(false) {}

void Texture::Generate(GLuint width, GLuint height, GLuint ch_n, int num, bool repeated, unsigned char *data)
{
    this->Width = width;
    this->Height = height;
    this->Channel_n = ch_n;
    this->texture_array_length = num;
    this->repeated = repeated;
    switch (ch_n)
    {
    case 1:
        this->Internal_Format = GL_RED;
        this->Image_Format = GL_RED;
        break;
    case 2:
        this->Internal_Format = GL_RG;
        this->Image_Format = GL_RG;
    case 3:
        this->Internal_Format = GL_RGB;
        this->Image_Format = GL_RGB;
        break;
    case 4:
        this->Internal_Format = GL_RGBA;
        this->Image_Format = GL_RGBA;
        break;
    default:
        std::cout << "ERROR::TEXTURE: Unsupported image format" << std::endl;
        break;
    }
    // // Create Texture
    // glGenTextures(1, &this->ID);
    // glBindTexture(GL_TEXTURE_2D, this->ID);
    // glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    // use texture array
    glGenTextures(1, &this->ID);
    glBindTexture(GL_TEXTURE_2D_ARRAY, this->ID);
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 0, this->Internal_Format, width, height, num);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, num, this->Internal_Format, GL_UNSIGNED_BYTE, data);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

// Binds the texture as the current active GL_TEXTURE_2D texture object
void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
}

int Texture::NextFrame()
{
    texture_index = (texture_index + 1) % texture_array_length;
    if (repeated)
        return texture_index;
    else
        return texture_index != 0 ? texture_index : -1;
}