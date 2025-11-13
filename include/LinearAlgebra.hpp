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
        struct mat4{
            float data[16];
        };
        
        LinearAlgebra() = delete;
        ~LinearAlgebra() = delete;
};

// LinearAlgebra::LinearAlgebra(/* args */)
// {
// }

// LinearAlgebra::~LinearAlgebra()
// {
// }
