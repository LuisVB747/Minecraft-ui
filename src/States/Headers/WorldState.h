#pragma once
#include "State.h"
#include "Chunk.h"
#include "ItemHandler.h"
#include "Camera.h"

class WorldState : public State {
private:
    std::vector<std::vector<std::vector<Chunk>>> world; // 5x5x5 grid of chunks
    ItemHandler* itemHandler; // Pointer to the item handler
    Camera camera; // Camera object
    ofVec3f playerPosition; // Player's position in the world
    bool isMouseHidden; // Track if the mouse is hidden
    float gravity;

public:
    /**
     * @brief Constructs a WorldState object.
     * @param player Pointer to the player object.
     * @param itemHandler Pointer to the item handler.
     */
    WorldState(Player* player, ItemHandler* itemHandler);

    /**
     * @brief Updates the state.
     */
    void update() override;

    /**
     * @brief Draws the state.
     */
    void draw() override;
    
    bool getIsMouseHidden(){return this->isMouseHidden;}

    /**
     * @brief Handles key press events.
     * @param key The key that was pressed.
     */
    void keyPressed(int key) override;

    /**
     * @brief Handles mouse movement events.
     * @param x The x-coordinate of the mouse.
     * @param y The y-coordinate of the mouse.
     */
    void mouseMoved(int x, int y) override;

    /**
     * @brief Handles mouse press events.
     * @param x The x-coordinate of the mouse.
     * @param y The y-coordinate of the mouse.
     * @param button The mouse button that was pressed.
     */
    void mousePressed(int x, int y, int button) override;

private:
    /**
     * @brief Loads or generates the 5x5x5 chunk world.
     */
    void loadWorld();

    /**
     * @brief Places a block at the specified position.
     * @param x The x-coordinate of the block.
     * @param y The y-coordinate of the block.
     * @param z The z-coordinate of the block.
     * @param block The block to place.
     */
    void placeBlock(int x, int y, int z, Block block);

    /**
     * @brief Removes a block at the specified position.
     * @param x The x-coordinate of the block.
     * @param y The y-coordinate of the block.
     * @param z The z-coordinate of the block.
     */
    void removeBlock(int x, int y, int z);

    /**
     * @brief Sets the current drawing color.
     * @param color The color to set.
     */
    void setColor(const Color& color);

    /**
     * @brief Draws a cube at the specified position.
     * @param x The x-coordinate of the cube's center.
     * @param y The y-coordinate of the cube's center.
     * @param z The z-coordinate of the cube's center.
     * @param size The size of the cube.
     */
    void drawCube(float x, float y, float z, float size);
};