#include "Camera.h"
#include <GL/gl.h> // Include OpenGL headers

Camera::Camera() {
    position.set(0, 0, 0); // Start at the origin
    target.set(0, 0, 0);   // Initially, same as position
    yaw = 0.0f;  
    pitch = 0.0f;  
    sensitivity = 0.01f;  

    // Initialize projection matrix (perspective projection)
    float fov = 60.0f;  
    float aspectRatio = ofGetWidth() / (float)ofGetHeight();  
    float nearClip = 0.1f;  
    float farClip = 1000.0f;  
    projectionMatrix.makePerspectiveMatrix(fov, aspectRatio, nearClip, farClip);
}

void Camera::update() {
    // Set position to target (player's position)
    position = target;

    // Calculate the forward direction based on yaw and pitch
    ofVec3f forward;
    forward.x = cos(ofDegToRad(yaw)) * cos(ofDegToRad(pitch));
    forward.y = sin(ofDegToRad(pitch));
    forward.z = sin(ofDegToRad(yaw)) * cos(ofDegToRad(pitch));
    forward.normalize();

    // Compute a right vector using the world up (0,1,0)
    ofVec3f right = forward.getCrossed(ofVec3f(0, 1, 0)).normalize();
    ofVec3f up = right.getCrossed(forward).normalize();

    // Build the view matrix (lookAt)
    viewMatrix.makeLookAtViewMatrix(position, position + forward, up);
}

void Camera::rotate(float deltaX, float deltaY) {
    yaw -= deltaX * sensitivity;  // Rotate left/right
    pitch -= deltaY * sensitivity;  // Rotate up/down

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
ofVec3f Camera::getForwardDirection() const {
    ofVec3f forward;
    forward.x = cos(ofDegToRad(yaw)) * cos(ofDegToRad(pitch));
    forward.y = sin(ofDegToRad(pitch));
    forward.z = sin(ofDegToRad(yaw)) * cos(ofDegToRad(pitch));
    forward.normalize(); // Ensure the vector has a length of 1
    return forward;
}
