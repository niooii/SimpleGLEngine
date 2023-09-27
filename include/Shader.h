#pragma once
#include <GL/glew.h>
#include <glm.hpp>

class Shader
{
public:
    Shader(const char* geom, const char* vert, const char* frag);
    Shader(const char* vert, const char* frag);

    void activate();
    //uniforms
    void setUniformMat3(const char* name, glm::mat3 val);
    void setUniformMat4(const char* name, glm::mat4 val);
    void setUniformVec3(const char* name, glm::vec3 val);
    void setUniformVec4(const char* name, glm::vec4 val);
    void setUniformFloat(const char* name, float val);

private:
    GLuint shaderProgram;

    std::string readFile(const char* pathToFile);
};