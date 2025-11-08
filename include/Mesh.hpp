#pragma once

#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl3.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>

struct vertex
{
    glm::vec3 position;
    glm::vec2 textureCoordinates;
};


class Mesh
{
    private:
        size_t vertexCount = 0;
        GLuint VAO = 0;
        GLuint VBO = 0;
    public:
        Mesh(const std::vector<vertex> &vertices);
        Mesh(Mesh &other) = delete;
        Mesh operator=(Mesh &other) = delete;
        ~Mesh();

        void draw() const;
};
