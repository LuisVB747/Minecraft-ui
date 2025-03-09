#include "Camera.h"
#include <GL/gl.h> // Include OpenGL headers

Camera::Camera() {
    position.set(0, 0, 0); // Start at the origin
    target.set(0, 0, 0); // Look at the origin
    yaw = 0.0f; // Initial horizontal rotation
    pitch = 0.0f; // Initial vertical rotation
    sensitivity = 0.1f; // Default mouse sensitivity
    distance = 10.0f; // Default distance from the player

    // Initialize projection matrix (perspective projection)
    float fov = 60.0f; // Field of view
    float aspectRatio = ofGetWidth() / (float)ofGetHeight(); // Aspect ratio
    float nearClip = 0.1f; // Near clipping plane
    float farClip = 1000.0f; // Far clipping plane
    projectionMatrix.makePerspectiveMatrix(fov, aspectRatio, nearClip, farClip);
}

void Camera::update() {
    // Calculate the camera's position based on the target and rotation
    position.x = target.x + distance * cos(ofDegToRad(yaw)) * cos(ofDegToRad(pitch));
    position.y = target.y + distance * sin(ofDegToRad(pitch));
    position.z = target.z + distance * sin(ofDegToRad(yaw)) * cos(ofDegToRad(pitch));

    // Calculate the view matrix using OpenGL
    glPushMatrix();
    glLoadIdentity();
    glRotatef(-pitch, 1, 0, 0); // Rotate vertically (up/down)
    glRotatef(-yaw, 0, 1, 0); // Rotate horizontally (left/right)
    glTranslatef(-position.x, -position.y, -position.z); // Move the camera to its position
    glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix.getPtr()); // Get the view matrix
    glPopMatrix();
}

void Camera::rotate(float deltaX, float deltaY) {
    yaw -= deltaX * sensitivity; // Negate deltaX to fix inverted horizontal rotation
    pitch -= deltaY * sensitivity; // Update vertical rotation

    // Clamp vertical rotation to avoid flipping
    pitch = ofClamp(pitch, -89.0f, 89.0f);
}

void Camera::setTarget(const ofVec3f& target) {
    this->target = target;
}

ofMatrix4x4 Camera::getViewMatrix() const {
    return viewMatrix;
}

ofMatrix4x4 Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

float Camera::getYaw() const {
    return yaw;
}

float Camera::getPitch() const {
    return pitch;
}

ofVec3f Camera::getPosition() const {
    return position;
}

void Camera::setSensitivity(float sensitivity) {
    this->sensitivity = sensitivity;
}

void Camera::setDistance(float distance) {
    this->distance = distance;
}