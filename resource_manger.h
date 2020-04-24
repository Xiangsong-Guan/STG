#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "texture.h"
#include "shader.h"

#include <glad/glad.h>

#include <unordered_map>
#include <string>

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no
// public constructor is defined.
class ResourceManager
{
public:
    // It is static
    ResourceManager() = delete;
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager(ResourceManager &&) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;
    ResourceManager &operator=(ResourceManager &&) = delete;
    ~ResourceManager() = delete;

    // Resource storage
    static std::unordered_map<std::string, Shader> Shaders;
    static std::unordered_map<std::string, Texture> Textures;
    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader &LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, const std::string &name);
    // Retrieves a stored sader
    static Shader &GetShader(const std::string &name);
    // Loads (and generates) a texture from file
    static Texture &LoadTexture(const GLchar *file, GLboolean alpha, const std::string &name);
    // Retrieves a stored texture
    static Texture &GetTexture(const std::string &name);
    // Properly de-allocates all loaded resources
    static void Clear();

private:
    // Loads and generates a shader from file
    static Shader load_shader_from_file(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
    // Loads a single texture from file
    static Texture load_texture_from_file(const GLchar *file, GLboolean alpha);
};

#endif