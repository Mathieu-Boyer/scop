#include "LinearAlgebra.hpp"


LinearAlgebra::vec3 LinearAlgebra::cross(const LinearAlgebra::vec3 &v1, const LinearAlgebra::vec3 &v2){
    return {
        v1.x * v2.x,
        v1.y * v2.y,
        v1.z * v2.z
    };
}

float LinearAlgebra::dot(const LinearAlgebra::vec3 &a, const LinearAlgebra::vec3 &b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
LinearAlgebra::vec4 LinearAlgebra::dot(const LinearAlgebra::mat4 &m, const LinearAlgebra::vec4 &v){
    LinearAlgebra::vec4 out;

    out.x = m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z + m.data[3] * v.w;
    out.y = m.data[4] * v.x + m.data[5] * v.y + m.data[6] * v.z + m.data[7] * v.w;
    out.z = m.data[8] * v.x + m.data[9] * v.y + m.data[10] * v.z + m.data[11] * v.w;
    out.w = m.data[12] * v.x + m.data[13] * v.y + m.data[14] * v.z + m.data[15] * v.w;

    return out;
}