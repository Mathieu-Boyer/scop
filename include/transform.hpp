#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct transform {

    transform();
    glm::vec3 rotation;
    glm::vec3 translation;
    glm::vec3 scale;
    glm::mat4 getModelMatrix() const;
};
