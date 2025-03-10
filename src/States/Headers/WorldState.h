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

        // Reference to the player's inventory
     std::vector<ItemContainer>& inventory; // Add this line
    const int WORLD_SIZE_X = 5 * 16; // 5 chunks * 16 blocks
    const int WORLD_SIZE_Z = 5 * 16; // 5 chunks * 16 blocks
    const int WORLD_MIN_Y = 0;       // Minimum Y level (e.g., bedrock)
    const int WORLD_MAX_Y = 256;     // Maximum Y level (e.g., sky limit)
     /**
     * @brief Performs raycasting to determine which block the player is looking at.
     * @param start The starting point of the ray (camera position).
     * @param end The end point of the ray (camera position + direction * distance).
     * @param blockX The x-coordinate of the block being looked at (output).
     * @param blockY The y-coordinate of the block being looked at (output).
     * @param blockZ The z-coordinate of the block being looked at (output).
     * @return True if a solid block is found, false otherwise.
     */
    bool raycast(const ofVec3f& start, const ofVec3f& end, int& blockX, int& blockY, int& blockZ);
    int selectedHotbarSlot; // Currently selected hotbar slot (0-8)


public:
    /**
     * @brief Constructs a WorldState object.
     * @param player Pointer to the player object.
     * @param itemHandler Pointer to the item handler.
     */
    WorldState(Player* player, ItemHandler* itemHandler);

    Block getBlockAt(int x, int y, int z) const; //gets block at xzy coordinates

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
     * @brief Draws the hotbar (bottom row of the inventory).
     */
    void drawHotbar();
    

    /**
     * @brief checks if the player is inside the world.
     */
    bool isWithinWorldBounds(float x, float y, float z) const;

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


    /**
     * @brief check if a block is solid at (x y z)
     * @param x The x coordinates
     * @param y The y coordinates
     * @param z The z coordinates
     */
    bool isColliding(float x, float y, float z);

    void drawCrosshair();

    // Check for collisions in all directions
    void checkCollisions();

    bool isPlayerOnGround();
};