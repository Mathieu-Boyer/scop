#pragma once

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
        };
        struct vec4{
            float x,y,z,w;
        };

        struct mat4{
            float data[16];
        };

        static vec3 cross(const vec3 &v1, const vec3 &v2);
        static float dot(const vec3 &a, const vec3 &b);
        static vec3 dot(const mat4 &m, const vec4 &v);

        LinearAlgebra() = delete;
        ~LinearAlgebra() = delete;
};

