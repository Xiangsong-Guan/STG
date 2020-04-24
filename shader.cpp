#include "shader.h"

void Shader::Use() const
{
    glUseProgram(ID);
}

void Shader::Compile(const GLchar *vertex_source, const GLchar *fragment_source, const GLchar *geometry_source)
{
    GLuint sVertex, sFragment, gShader;
    // Vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertex_source, NULL);
    glCompileShader(sVertex);
    check_compile_error(sVertex, "VERTEX");
    // Fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragment_source, NULL);
    glCompileShader(sFragment);
    check_compile_error(sFragment, "FRAGMENT");
    // If geometry shader source code is given, also compile geometry shader
    if (geometry_source != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometry_source, NULL);
        glCompileShader(gShader);
        check_compile_error(gShader, "GEOMETRY");
    }
    // Shader Program
    ID = glCreateProgram();
    glAttachShader(ID, sVertex);
    glAttachShader(ID, sFragment);
    if (geometry_source != nullptr)
        glAttachShader(ID, gShader);
    glLinkProgram(ID);
    check_compile_error(ID, "PROGRAM");
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometry_source != nullptr)
        glDeleteShader(gShader);
}

void Shader::SetFloat(const GLchar *name, GLfloat value) const
{
    glUniform1f(glGetUniformLocation(ID, name), value);
}
void Shader::SetInteger(const GLchar *name, GLint value) const
{
    glUniform1i(glGetUniformLocation(ID, name), value);
}
void Shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y) const
{
    glUniform2f(glGetUniformLocation(ID, name), x, y);
}
void Shader::SetVector2f(const GLchar *name, const glm::vec2 &value) const
{
    glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
}
void Shader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z) const
{
    glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}
void Shader::SetVector3f(const GLchar *name, const glm::vec3 &value) const
{
    glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
}
void Shader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const
{
    glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}
void Shader::SetVector4f(const GLchar *name, const glm::vec4 &value) const
{
    glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::check_compile_error(GLuint object, std::string type) const
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- "
                      << std::endl;
        }
    }
}
