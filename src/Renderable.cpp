#include "Renderable.hpp"


Renderable::Renderable(Mesh &mesh, Texture *texture) : mesh(mesh), texture(texture){}

void Renderable::draw(Shaders &shader){

    shader.use();
    if (texture)
        texture->bind();
    shader.setMat4("model", transform.getModelMatrix());
    mesh.draw();
}

s_transform &Renderable::getTransform() {
    return transform;
}

const s_transform &Renderable::getTransform() const{
    return transform;
}