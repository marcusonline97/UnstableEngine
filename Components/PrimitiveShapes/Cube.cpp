#include "Cube.h"
#include <iostream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>

// vertex / fragment sources
static const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

static const char* fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;
uniform vec3 uColor;
void main()
{
    FragColor = vec4(uColor, 1.0);
}
)";

static GLuint CompileShader(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetShaderiv(s, GL_INFO_LOG_LENGTH, &len);
        std::string log(len > 0 ? len : 1, ' ');
        glGetShaderInfoLog(s, len, nullptr, &log[0]);
        std::cerr << "Shader compile error: " << log << "\n";
        glDeleteShader(s);
        return 0;
    }
    return s;
}

GLuint Cube::CompileShaderProgram(const char* vertSrc, const char* fragSrc) {
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertSrc);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragSrc);
    if (!vs || !fs) {
        if (vs) glDeleteShader(vs);
        if (fs) glDeleteShader(fs);
        return 0;
    }

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    GLint ok = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
        std::string log(len > 0 ? len : 1, ' ');
        glGetProgramInfoLog(prog, len, nullptr, &log[0]);
        std::cerr << "Program link error: " << log << "\n";
        glDeleteProgram(prog);
        prog = 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}

void Cube::SetupCube() {
    float vertices[] = {
        // positions (36 vertices)
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Cube::Cube() : model(glm::mat4(1.0f)), VAO(0), VBO(0), shaderProgram(0),
    locModel(-1), locView(-1), locProj(-1), locColor(-1)
{
    shaderProgram = CompileShaderProgram(vertexShaderSrc, fragmentShaderSrc);
    if (!shaderProgram) {
        std::cerr << "Failed to create cube shader program\n";
        return;
    }

    // cache uniform locations once
    locModel = glGetUniformLocation(shaderProgram, "model");
    locView = glGetUniformLocation(shaderProgram, "view");
    locProj = glGetUniformLocation(shaderProgram, "projection");
    locColor = glGetUniformLocation(shaderProgram, "uColor");

    SetupCube();
}

Cube::~Cube() {
    if (shaderProgram) glDeleteProgram(shaderProgram);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
}

void Cube::SetRotation(float angle, const glm::vec3& axis) {
    // normalize axis to avoid scaling issues
    glm::vec3 n = axis;
    if (glm::length(n) > 1e-6f) n = glm::normalize(n);
    else n = glm::vec3(0.0f, 1.0f, 0.0f);

    model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), n);
}

void Cube::Render(const glm::mat4& view, const glm::mat4& projection) {
    if (!shaderProgram) return;
    glUseProgram(shaderProgram);

    if (locModel >= 0) glUniformMatrix4fv(locModel, 1, GL_FALSE, &model[0][0]);
    if (locView >= 0)  glUniformMatrix4fv(locView,  1, GL_FALSE, &view[0][0]);
    if (locProj >= 0)  glUniformMatrix4fv(locProj,  1, GL_FALSE, &projection[0][0]);
    if (locColor >= 0) glUniform3f(locColor, 0.8f, 0.6f, 0.2f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glUseProgram(0);
}