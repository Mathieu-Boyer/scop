#pragma once
#include "Mesh.hpp"
#include "Texture.hpp"
#include "transform.hpp"
#include "Shaders.hpp"

class Renderable
{
    private:
        Mesh &mesh;
        Texture *texture;
        s_transform transform{};

    public:
        Renderable(Mesh &mesh, Texture *texture);
        void draw(Shaders &shader);
        s_transform &getTransform();
        const s_transform &getTransform() const;
};