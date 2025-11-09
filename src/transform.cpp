#include "transform.hpp"

transform::transform() : rotation(0.0f), translation(0.0f), scale(1.f){}

glm::mat4 transform::getModelMatrix() const{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1,0,0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0,1,0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0,0,1));
    model = glm::translate(model, translation);
    return model;
}