#pragma once
#include <cmath>
#include <array>
class LinearAlgebra
{
    private:
        /* data */
    public:

        struct vec2{
            float x,y;
        };
        struct vec3{
            float x,y,z;
            vec3 operator+(const vec3 &rhs) const;
            vec3 operator-(const vec3 &rhs) const;
            float computeMagnitude() const;
        };
        struct vec4{
            float x,y,z,w;
        };

        struct mat4{
            std::array<float, 16> data;
            mat4() = default;
            mat4(float diag);
        };

        static vec3 cross(const vec3 &v1, const vec3 &v2);
        static vec3 normalize(const vec3 &v);
        static vec3 add(const vec3 &v1, const vec3 &v2);
        static vec3 sub(const vec3 &v1, const vec3 &v2);
        static float dot(const vec3 &a, const vec3 &b);
        static vec4 matMul(const mat4 &m, const vec4 &v);
        static mat4 matMul(const LinearAlgebra::mat4 &a, const LinearAlgebra::mat4 &b);

        static mat4 scale(const mat4 &a, const vec3 &b);
        static mat4 translate(const LinearAlgebra::mat4 &a, const LinearAlgebra::vec3 &b);
        static mat4 rotateX(float rad);
        static mat4 rotateY(float rad);
        static mat4 rotateZ(float rad);
        static mat4 rotate(const mat4 &model, float rad, const vec3 &axis);

        static mat4 lookAt(vec3 eye, vec3 center, vec3 up) {
            vec3 f = normalize(center - eye);
            vec3 s = normalize(cross(f, up));
            vec3 u = cross(s, f);
            
            mat4 result;
            result.data[0] = s.x;
            result.data[1] = u.x;
            result.data[2] = -f.x;
            result.data[3] = 0;
            
            result.data[4] = s.y;
            result.data[5] = u.y;
            result.data[6] = -f.y;
            result.data[7] = 0;
            
            result.data[8] = s.z;
            result.data[9] = u.z;
            result.data[10] = -f.z;
            result.data[11] = 0;
            
            result.data[12] = -dot(s, eye);
            result.data[13] = -dot(u, eye);
            result.data[14] = dot(f, eye);
            result.data[15] = 1;
            
            return result;
        }

        static mat4 perspective(float fovY_rad, float aspect, float near, float far) {
            float tanHalfFovy = tan(fovY_rad / 2.0f);
            
            mat4 result = {0};
            
            result.data[0] = 1.0f / (aspect * tanHalfFovy);  // [0][0]
            result.data[5] = 1.0f / tanHalfFovy;             // [1][1]
            result.data[10] = -(far + near) / (far - near);  // [2][2]
            result.data[11] = -1.0f;                         // [2][3]
            result.data[14] = -(2.0f * far * near) / (far - near); // [3][2]
            
            return result;
        }


        LinearAlgebra() = delete;
        ~LinearAlgebra() = delete;
};

