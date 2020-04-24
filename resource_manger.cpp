#include "resource_manger.h"

#include "stb_image.h"

#include <iostream>
#include <sstream>
#include <fstream>

// Instantiate static variables
std::unordered_map<std::string, Texture> ResourceManager::Textures;
std::unordered_map<std::string, Shader> ResourceManager::Shaders;

Shader &ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, const std::string &name)
{
    Shaders[name] = load_shader_from_file(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader &ResourceManager::GetShader(const std::string &name)
{
    return Shaders.at(name);
}

Texture &ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, const std::string &name)
{
    Textures[name] = load_texture_from_file(file, alpha);
    return Textures[name];
}

Texture &ResourceManager::GetTexture(const std::string &name)
{
    return Textures.at(name);
}

void ResourceManager::Clear()
{
    // (Properly) delete all shaders
    for (auto const &[_, v] : Shaders)
        glDeleteProgram(v.ID);
    // (Properly) delete all textures
    for (auto const &[_, v] : Textures)
        glDeleteTextures(1, &v.ID);
    Shaders.clear();
    Textures.clear();
}

Shader ResourceManager::load_shader_from_file(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "| ERROR::SHADER: Failed to read shader files"
                  << e.what() << "\n-- ----------------------------------------------- --"
                  << std::endl;
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    // 2. Now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture ResourceManager::load_texture_from_file(const GLchar *file, GLboolean alpha)
{
    // Create Texture object
    Texture texture;
    // Load image
    int width, height, ch_n;
    unsigned char *image = stbi_load(file, &width, &height, &ch_n, 0);
    if (image)
        // Now generate texture
        texture.Generate(width, height, ch_n, image);
    else
        std::cout << "ERROR::TEXTURE: Fail to load texture file" << std::endl;
    // And finally free image data
    stbi_image_free(image);
    return texture;
}