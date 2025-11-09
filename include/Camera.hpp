#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:


    float fov;
    float aspect ;
    float near;
    float far;

    float yaw;
    float pitch;

    glm::vec3 position;
    glm::vec3 worldUp;

    glm::vec3 localUp;
    glm::vec3 localFront;
    glm::vec3 localRight;

public:
    Camera(const glm::vec3 &pos, float fov=45, float aspect=1.0, float near=0.1, float far=100);
    void updateCameraRotation();
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    void setProjectionMatrix(float fov, float aspect, float near, float far);
    ~Camera();
};




