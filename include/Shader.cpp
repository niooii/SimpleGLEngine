#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"

Shader::Shader(const char* geom, const char* vert, const char* frag)
{
    int success;
    char infoLog[512];

    GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &geom, nullptr);
    glCompileShader(geometryShader);
    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
        //
    }

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vert, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        //
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &frag, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        //
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, geometryShader);
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(geometryShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::Shader(const char *vert, const char *frag)
{
    int success;
    char infoLog[512];

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertStr = readFile(vert);
    const char* vertSrc = vertStr.c_str();
    glShaderSource(vertexShader, 1, &vertSrc, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "vertex not compiled: " << infoLog << '\n';
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragStr = readFile(frag);
    const char* fragSrc = fragStr.c_str();
    glShaderSource(fragmentShader, 1, &fragSrc, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "fragment not compiled: " << infoLog << '\n';
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::activate()
{
    glUseProgram(shaderProgram);
}


void Shader::setUniformMat3(const char* name, glm::mat3 val) {
    GLuint loc = glGetUniformLocation(shaderProgram, name);
    if (loc == -1) {
        std::cerr << "Uniform '" << name << "' not found in shader." << std::endl;
        return;
    }
    glUniformMatrix3fv(loc, 1, GL_FALSE, &val[0][0]);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after setting uniform '" << name << "': " << gluErrorString(error) << std::endl;
    }
}

void Shader::setUniformMat4(const char* name, glm::mat4 val)
{
    // Get the uniform location
    GLuint loc = glGetUniformLocation(shaderProgram, name);

    // Check if the uniform location is valid
    if (loc == -1)
    {
        // Handle the case where the uniform does not exist
        std::cerr << "Uniform '" << name << "' not found in shader." << std::endl;
        return; // You can choose to return or throw an exception here
    }

    // Set the uniform value
    glUniformMatrix4fv(loc, 1, GL_FALSE, &val[0][0]);

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error after setting uniform '" << name << "': " << gluErrorString(error) << std::endl;
        // You can choose to return or throw an exception here
    }
}

void Shader::setUniformVec3(const char* name, glm::vec3 val) {
    GLuint loc = glGetUniformLocation(shaderProgram, name);
    if (loc == -1) {
        std::cerr << "Uniform '" << name << "' not found in shader." << std::endl;
        return;
    }
    glUniform3fv(loc, 1, &val[0]);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after setting uniform '" << name << "': " << gluErrorString(error) << std::endl;
    }
}

void Shader::setUniformVec4(const char* name, glm::vec4 val) {
    GLuint loc = glGetUniformLocation(shaderProgram, name);
    if (loc == -1) {
        std::cerr << "Uniform '" << name << "' not found in shader." << std::endl;
        return;
    }
    glUniform4fv(loc, 1, &val[0]);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after setting uniform '" << name << "': " << gluErrorString(error) << std::endl;
    }
}

void Shader::setUniformFloat(const char* name, float val) {
    GLuint loc = glGetUniformLocation(shaderProgram, name);
    if (loc == -1) {
        std::cerr << "Uniform '" << name << "' not found in shader." << std::endl;
        return;
    }
    glUniform1f(loc, val);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after setting uniform '" << name << "': " << gluErrorString(error) << std::endl;
    }
}

std::string Shader::readFile(const char* pathToFile)
{
    std::string content;
    std::ifstream fstream{};
    fstream.open(pathToFile);

    if(!fstream.is_open()) {
        std::cerr << "Could not read file " << pathToFile << ". File does not exist." << std::endl;
        return "";
    }

    std::stringstream s{};
    s << fstream.rdbuf();

    fstream.close();
    return s.str();
}
