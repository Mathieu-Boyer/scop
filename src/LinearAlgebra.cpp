#include "LinearAlgebra.hpp"


LinearAlgebra::vec3 LinearAlgebra::cross(const LinearAlgebra::vec3 &a, const LinearAlgebra::vec3 &b){
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x,
    };
}

float LinearAlgebra::dot(const LinearAlgebra::vec3 &a, const LinearAlgebra::vec3 &b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

LinearAlgebra::vec3 LinearAlgebra::add(const LinearAlgebra::vec3 &a, const LinearAlgebra::vec3 &b){
    return {a.x + b.x , a.y + b.y , a.z + b.z};
}

LinearAlgebra::vec3 LinearAlgebra::sub(const LinearAlgebra::vec3 &a, const LinearAlgebra::vec3 &b){
    return {a.x - b.x , a.y - b.y , a.z - b.z};
}

LinearAlgebra::vec3 LinearAlgebra::normalize(const vec3 &v){
    float magnitude = v.computeMagnitude();
    if (magnitude == 0.0f) return {0.0f, 0.0f, 0.0f}; // or maybe i will it throw error i'm not sure yet
    return {v.x / magnitude, v.y / magnitude, v.z / magnitude};
}


LinearAlgebra::vec4 LinearAlgebra::dot(const LinearAlgebra::mat4 &m, const LinearAlgebra::vec4 &v){
    LinearAlgebra::vec4 out;

    out.x = m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z + m.data[3] * v.w;
    out.y = m.data[4] * v.x + m.data[5] * v.y + m.data[6] * v.z + m.data[7] * v.w;
    out.z = m.data[8] * v.x + m.data[9] * v.y + m.data[10] * v.z + m.data[11] * v.w;
    out.w = m.data[12] * v.x + m.data[13] * v.y + m.data[14] * v.z + m.data[15] * v.w;

    return out;
}

LinearAlgebra::vec3 LinearAlgebra::vec3::operator+(const vec3 &rhs) const{
    return LinearAlgebra::add(*this, rhs);
}
LinearAlgebra::vec3 LinearAlgebra::vec3::operator-(const vec3 &rhs) const{
    return LinearAlgebra::sub(*this, rhs);
}

float LinearAlgebra::vec3::computeMagnitude() const{
    return (std::sqrt(
        x*x + y*y + z*z
    ));
}