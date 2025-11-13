#pragma once
#include "LinearAlgebra.hpp"
#include "utils.hpp"


class Camera
{
private:


    float fov;
    float aspect ;
    float near;
    float far;

    float yaw;
    float pitch;

    LinearAlgebra::vec3 position;
    LinearAlgebra::vec3 worldUp;

    LinearAlgebra::vec3 localUp;
    LinearAlgebra::vec3 localFront;
    LinearAlgebra::vec3 localRight;

public:
    Camera(const LinearAlgebra::vec3 &pos, float fov=45, float aspect=1.0, float near=0.1, float far=100);
    void updateCameraRotation();
    LinearAlgebra::mat4 getViewMatrix() const;
    LinearAlgebra::mat4 getProjectionMatrix() const;
    void setProjectionMatrix(float fov, float aspect, float near, float far);
    ~Camera();
};




