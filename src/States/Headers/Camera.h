#pragma once
#include "ofMain.h"

class Camera {
private:
    ofVec3f position; // Camera position
    ofVec3f target;   // Camera target (player position)
    float yaw;       // Horizontal rotation (left/right)
    float pitch;     // Vertical rotation (up/down)
    float sensitivity; // Mouse sensitivity
    float distance;  // Distance from the player

    ofMatrix4x4 viewMatrix; // View matrix (camera transform)
    ofMatrix4x4 projectionMatrix; // Projection matrix

public:
    /**
     * @brief Constructs a Camera object.
     */
    Camera();

    /**
     * @brief Updates the camera's position and view matrix.
     */
    void update();

    /**
     * @brief Rotates the camera based on mouse movement.
     * @param deltaX Change in mouse X position.
     * @param deltaY Change in mouse Y position.
     */
    void rotate(float deltaX, float deltaY);

    /**
     * @brief Sets the camera's target (player position).
     * @param target The new target position.
     */
    void setTarget(const ofVec3f& target);

    /**
     * @brief Gets the view matrix.
     * @return The view matrix.
     */
    ofMatrix4x4 getViewMatrix() const;

    /**
     * @brief Gets the projection matrix.
     * @return The projection matrix.
     */
    ofMatrix4x4 getProjectionMatrix() const;

    /**
     * @brief Gets the camera's yaw (horizontal rotation).
     * @return The yaw angle.
     */
    float getYaw() const;

    /**
     * @brief Gets the camera's pitch (vertical rotation).
     * @return The pitch angle.
     */
    float getPitch() const;

    /**
     * @brief Gets the camera's position.
     * @return The camera position.
     */
    ofVec3f getPosition() const;

    /**
     * @brief Sets the mouse sensitivity.
     * @param sensitivity The new mouse sensitivity.
     */
    void setSensitivity(float sensitivity);

    /**
     * @brief Sets the distance from the player.
     * @param distance The new distance.
     */
    void setDistance(float distance);

        /**
     * @brief Gets the forward direction vector of the camera.
     * @return The forward direction vector.
     */
    ofVec3f getForwardDirection() const;
};