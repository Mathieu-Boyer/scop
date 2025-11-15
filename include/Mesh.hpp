#pragma once

#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

#ifdef __linux__
#include <GL/gl.h>
#endif
#include "GLFW/glfw3.h"
#include <vector>
#include <iostream>
#include "vertex.hpp"
#include "OBJParser.hpp"


class Mesh
{
    private:
        size_t vertexCount = 0;
        GLuint VAO = 0;
        GLuint VBO = 0;
        GLuint VEO = 0;
        OBJ objData;
    public:
        Mesh(const std::vector<vertex> &vertices, OBJ objedata);
        Mesh(Mesh &other) = delete;
        Mesh operator=(Mesh &other) = delete;
        ~Mesh();

        void draw() const;
};
