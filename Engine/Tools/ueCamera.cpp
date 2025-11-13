#include "ueCamera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <glm/gtc/quaternion.hpp>
//#include logger

ueCamera::ueCamera(ueCameraProjection projection)
{
	if (projection == ueCameraProjection::Orthographic)
	{
		setOrthographicProjection(512, 512, 1000.f, -1000.f);
	}
	else
	{
		setPerspectiveProjection(90.f, 512, 512, 1000.f, -1000.f);
	}
}

void ueCamera::setPerspectiveProjection(
    float fov, uint32_t screenWidth, uint32_t screenHeight, float farPlane, float nearPlane)
{
    _projectionType = ueCameraProjection::Perspective;

    _projectionMatrix =
        glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, nearPlane, farPlane);

    // Flip the Y coordinate
    _projectionMatrix[1][1] *= -1.f;
}

void ueCamera::setOrthographicProjection(uint32_t screenWidth, uint32_t screenHeight, float farPlane, float nearPlane)
{
    _projectionType = ueCameraProjection::Orthographic;
    _projectionMatrix = glm::ortho(-((float)screenWidth / 2.0f),
        ((float)screenWidth / 2.0f),
        ((float)screenHeight / 2.0f),
        -((float)screenHeight / 2.0f),
        nearPlane,
        farPlane);
}

void ueCamera::setViewMatrix(const glm::mat4& view, const glm::vec3& position)
{
    _viewMatrix = view;
    _position = position;
}

glm::mat4 ueCamera::getProjectionViewMatrix() const
{
    return _projectionMatrix * _viewMatrix;
}

glm::mat4 ueCamera::getProjectionMatrix() const
{
    return _projectionMatrix;
}

glm::mat4 ueCamera::getViewMatrix() const
{
    return _viewMatrix;
}

glm::vec3 ueCamera::getPosition() const
{
    return _position;
}
void ueCamera::setBackgroundColor(const glm::vec3& color)
{
    _backgroundColor = color;
}

glm::vec3 ueCamera::getBackgroundColor() const
{
    return _backgroundColor;
}

ueCameraProjection ueCamera::getProjectionType() const
{
    return _projectionType;
}

glm::mat4 ueCameraSimpleFPVController::getLookAtViewMatrix() const
{
    return glm::lookAt(position, position + _front, _up);
}

void ueCameraSimpleFPVController::setPerspectiveMouseSensitivity(float sensitivity)
{
    _mouseSensitivity = sensitivity;
}

void ueCameraSimpleFPVController::applyPerspectiveMouseMovementDelta(glm::vec2 delta, float factor)
{
    delta *= _mouseSensitivity * factor;
    yaw = glm::mod(yaw + delta.x, 360.0f);
    pitch += delta.y;

    pitch = glm::clamp(pitch, -89.f, 89.f);

    calculatePerspectiveVectors();
}

// TODO:
// https://gitlab.com/muffinman007/OpenGL_360_Camera_Quarternion/blob/master/Camera.h 
// /* probably waste of time */ 

void ueCameraSimpleFPVController::calculatePerspectiveVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    _front = glm::normalize(front);
    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));

    if (pitch > 90.f || pitch < 270.f) {
        _right *= -1;
    }
}

void ueCameraSimpleFPVController::moveForward(float speed)
{
    position += _front * speed;
}

void ueCameraSimpleFPVController::moveBackward(float speed)
{
    position -= _front * speed;
}

void ueCameraSimpleFPVController::moveRight(float speed)
{
    position -= _right * speed;
}

void ueCameraSimpleFPVController::moveLeft(float speed)
{
    position += _right * speed;
}

void ueCameraSimpleFPVController::moveUp(float speed)
{
    position -= _up * speed;
}

void ueCameraSimpleFPVController::moveDown(float speed)
{
    position += _up * speed;
}

void ueCameraSimpleFPVController::move(glm::vec3 v)
{
    position += v;
}

void ueCameraSimpleFPVController::backToOrigin()
{
    position = { 0.f, 0.f, 0.f };
    _front = { 0.0f, 0.0f, -1.0f };
    _up = { 0.0f, 1.0f, 0.0f };
    _right = glm::vec3{};
    yaw = -90.f;
    pitch = 0.f;
    applyPerspectiveMouseMovementDelta({ 0, 0 }, 0.f);
}
void ueCameraSimpleFPVController::setPitch(float pitch)
{
    pitch = pitch;
}
void ueCameraSimpleFPVController::setYaw(float yaw)
{
    yaw = yaw;
}
void ueCameraSimpleFPVController::recalculateVectorsFromViewMatrix(const glm::mat4& view)
{
    glm::quat rotation = glm::quat_cast(view);
    yaw = glm::degrees(glm::yaw(rotation));
    pitch = glm::degrees(glm::pitch(rotation));
    //LOGV << "YAW: " << yaw << ", PITCH: " << pitch;
    calculatePerspectiveVectors();
}