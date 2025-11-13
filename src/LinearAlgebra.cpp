#include "LinearAlgebra.hpp"


LinearAlgebra::vec3 LinearAlgebra::cross(const LinearAlgebra::vec3 &v1, const LinearAlgebra::vec3 &v2){
    return {v1.x * v2.x,
            v1.y * v2.y,
            v1.z * v2.z};
}