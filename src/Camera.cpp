# include "Camera.hpp"
# include "iostream"

Camera::Camera(const glm::vec3 &pos, float fov, float aspect, float near, float far) : fov(fov) , aspect(aspect), near(near), far(far)
{
    position = pos;
    worldUp = {0,1,0};
    yaw = -90;
    pitch = 0;

    updateCameraRotation();
}

void Camera::updateCameraRotation()
{
    localFront = glm::normalize((glm::vec3){
        cos(glm::radians(pitch)) * cos(glm::radians(yaw)),
        sin(glm::radians(pitch)),
        cos(glm::radians(pitch)) * sin(glm::radians(yaw)),
    });
    localRight = glm::normalize(glm::cross(localFront, worldUp));
    localUp = glm::normalize(glm::cross(localRight, localFront));
}

glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(position, position + localFront, localUp);
}

glm::mat4 Camera::getProjectionMatrix() const{
    return glm::perspective(glm::radians(fov), aspect, near, far);
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