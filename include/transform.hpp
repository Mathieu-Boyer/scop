#pragma once
#include "LinearAlgebra.hpp"
#include "utils.hpp"

typedef struct transform {
    transform();
    LinearAlgebra::vec3 rotation;
    LinearAlgebra::vec3 translation;
    LinearAlgebra::vec3 scale;
    LinearAlgebra::mat4 getModelMatrix() const;
} s_transform;
