#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class Cube {
public:
    Cube();
    ~Cube();
    void SetRotation(float angle, const glm::vec3& axis);
    void Render(const glm::mat4& view, const glm::mat4& projection);

private:
    void SetupCube();
    GLuint CompileShaderProgram(const char* vertSrc, const char* fragSrc);

    glm::mat4 model;
    GLuint VAO, VBO;
    GLuint shaderProgram;

    // cached uniform locations
    GLint locModel = -1;
    GLint locView = -1;
    GLint locProj = -1;             
    GLint locColor = -1;
};