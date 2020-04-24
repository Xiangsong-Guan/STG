#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

class Shader
{
public:
    GLuint ID;

    Shader() = default;
    Shader(const Shader &) = default;
    Shader(Shader &&) = default;
    Shader &operator=(const Shader &) = default;
    Shader &operator=(Shader &&) = default;
    ~Shader() = default;

    void Use() const;
    void Compile(const GLchar *vertex_source, const GLchar *fragment_source, const GLchar *geometry_source = nullptr);

    void SetFloat(const GLchar *name, GLfloat value) const;
    void SetInteger(const GLchar *name, GLint value) const;
    void SetVector2f(const GLchar *name, GLfloat x, GLfloat y) const;
    void SetVector2f(const GLchar *name, const glm::vec2 &value) const;
    void SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z) const;
    void SetVector3f(const GLchar *name, const glm::vec3 &value) const;
    void SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
    void SetVector4f(const GLchar *name, const glm::vec4 &value) const;
    void SetMatrix4(const GLchar *name, const glm::mat4 &matrix) const;

private:
    void check_compile_error(GLuint object, std::string type) const;
};

#endif