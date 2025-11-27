# include "Camera.hpp"
# include "iostream"

Camera::Camera(const LinearAlgebra::vec3 &pos, float fov, float aspect, float near, float far) : fov(fov) , aspect(aspect), near(near), far(far)
{
    position = pos;
    worldUp = {0,1,0};
    yaw = -90;
    pitch = 0;

    updateCameraRotation();
}

void Camera::updateCameraRotation()
{
    localFront = LinearAlgebra::normalize((LinearAlgebra::vec3){
        static_cast<float>(cos(degToRad(pitch))) * static_cast<float>(cos(degToRad(yaw))),
        static_cast<float>(sin(degToRad(pitch))),
        static_cast<float>(cos(degToRad(pitch))) * static_cast<float>(sin(degToRad(yaw))),
    });
    localRight = LinearAlgebra::normalize(LinearAlgebra::cross(localFront, worldUp));
    localUp = LinearAlgebra::normalize(LinearAlgebra::cross(localRight, localFront));
}

LinearAlgebra::mat4 Camera::getViewMatrix() const{
    return LinearAlgebra::lookAt(position, position + localFront, localUp);
}

LinearAlgebra::mat4 Camera::getProjectionMatrix() const{
    return LinearAlgebra::perspective(degToRad(fov), aspect, near, far);
}

void Camera::setProjectionMatrix(float fov, float aspect, float near, float far){
    this->fov = fov;
    this->aspect = aspect;
    this->near = near;
    this->far = far;
}

Camera::~Camera()
{
}