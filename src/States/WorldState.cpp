#include "WorldState.h"
#include <GL/gl.h> // Include OpenGL headers
#include <GL/glu.h> // Include GLU utilities
#include <GLFW/glfw3.h> // Include GLFW for input handling

WorldState::WorldState(Player* player, ItemHandler* itemHandler)
    : State(player), inventory(player->getInventory()), selectedHotbarSlot(0)  {
    this->itemHandler = itemHandler;
    isMouseHidden = false; // Track mouse visibility
    gravity = 0.1; //constant for the gravity

    // Initialize player position
    playerPosition.set(40, 10, 40); // Start the player above the ground

    // Initialize the camera
    camera.setSensitivity(0.1f); // Set mouse sensitivity
    

    loadWorld(); // Load or generate the world
}

bool WorldState::isWithinWorldBounds(float x, float y, float z) const {
    return x >= 0 && x < WORLD_SIZE_X &&
           z >= 0 && z < WORLD_SIZE_Z &&
           y >= WORLD_MIN_Y && y < WORLD_MAX_Y;
}
void WorldState::drawCrosshair() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); // Save the current projection matrix
    glLoadIdentity();
    
    // Set an orthographic projection (2D mode)
    gluOrtho2D(0, ofGetWidth(), 0, ofGetHeight());

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix(); // Save the current model-view matrix
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); // Disable depth test so the crosshair is always visible

    // Set crosshair color (white)
    glColor3f(1.0f, 1.0f, 1.0f);

    // Get screen center
    float centerX = ofGetWidth() / 2.0f;
    float centerY = ofGetHeight() / 2.0f;
    float crosshairSize = 10.0f; // Length of the crosshair lines

    // Draw crosshair using OpenGL lines
    glBegin(GL_LINES);
        // Horizontal line
        glVertex2f(centerX - crosshairSize, centerY);
        glVertex2f(centerX + crosshairSize, centerY);

        // Vertical line
        glVertex2f(centerX, centerY - crosshairSize);
        glVertex2f(centerX, centerY + crosshairSize);
    glEnd();

    glEnable(GL_DEPTH_TEST); // Re-enable depth testing

    // Restore previous matrices
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void WorldState::update() {
    camera.setTarget(playerPosition); // Update camera target to follow the player
    camera.update(); // Update the camera's position

        // Apply gravity (if implemented)
        gravity -= 0.1f;
        playerPosition.y += gravity;

        // checks if the player is outside the world:
        if (!isWithinWorldBounds(playerPosition.x, playerPosition.y, playerPosition.z)) {
            // Reset the player to the nearest valid position
            playerPosition.x = ofClamp(playerPosition.x, 0, WORLD_SIZE_X - 1);
            playerPosition.z = ofClamp(playerPosition.z, 0, WORLD_SIZE_Z - 1);
            playerPosition.y = ofClamp(playerPosition.y, WORLD_MIN_Y, WORLD_MAX_Y - 1);
        }
    
        // Check for ground collision
        if (isPlayerOnGround()) {
            gravity = 0.0f;
            playerPosition.y = round(playerPosition.y);
        }
    
        // Check for collisions in all directions
        checkCollisions();
    }

bool WorldState::isPlayerOnGround(){
        // Check the block directly below the player
        int blockX = static_cast<int>(playerPosition.x);
        int blockY = static_cast<int>(playerPosition.y - 1); // Block below the player
        int blockZ = static_cast<int>(playerPosition.z);
    
        // Check if the block is solid
        Block block = getBlockAt(blockX, blockY, blockZ);
        return block.getType() != 0; // 0 = air (not solid)
    }

void WorldState::draw() {
    ofEnableDepthTest(); // Enable depth testing for 3D rendering

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(camera.getProjectionMatrix().getPtr());

    // Set up the view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(camera.getViewMatrix().getPtr());

    // Draw the world
    const int CHUNK_SIZE = 16;
    const int BLOCK_SIZE = 1;

    for (int cx = 0; cx < 5; ++cx) {
        for (int cz = 0; cz < 5; ++cz) {
            for (int x = 0; x < CHUNK_SIZE; ++x) {
                for (int y = 0; y < CHUNK_SIZE; ++y) {
                    for (int z = 0; z < CHUNK_SIZE; ++z) {
                        Block block = world[cx][0][cz].getBlock(x, y, z);
                        if (block.getType() != 0) { // If not air
                            setColor(block.getColor()); // Set the block's color
                            drawCube((cx * CHUNK_SIZE + x) * BLOCK_SIZE,
                                     y * BLOCK_SIZE,
                                     (cz * CHUNK_SIZE + z) * BLOCK_SIZE,
                                     BLOCK_SIZE); // Draw the block
                        }
                    }
                }
            }
        }
    }
    drawCrosshair();
    ofDisableDepthTest(); // Disable depth testing
    // drawHotbar();
}

void WorldState::keyPressed(int key) {
    float moveSpeed = 1.0f; // Adjust movement speed as needed

    // Get the camera's forward and right vectors
    ofVec3f forward = camera.getForwardDirection();
    ofVec3f right = forward.getCrossed(ofVec3f(0, 1, 0)).normalize(); // Right vector is perpendicular to forward and world up

    // if (key >= '1' && key <= '9') {
    //     selectedHotbarSlot = key - '1';} // Convert key to slot index (0-8)
    // // Calculate the new position based on input
    ofVec3f newPosition = playerPosition;

    if (key == 'w' || key == 'W') { // Move forward
        newPosition += forward * moveSpeed;
    }
    if (key == 's' || key == 'S') { // Move backward
        newPosition -= forward * moveSpeed;
    }
    if (key == 'a' || key == 'A') { // Move left
        newPosition -= right * moveSpeed;
    }
    if (key == 'd' || key == 'D') { // Move right
        newPosition += right * moveSpeed;
    }
    if (key == ' ') { // Jump
        if (isPlayerOnGround()) {
            gravity = 2.0f;
        }
    }
    if (key == OF_KEY_CONTROL) { // Crouch
        newPosition.y -= moveSpeed;
    }

    // Check if the new position is valid (no collisions)
    if (!isColliding(newPosition.x, newPosition.y, newPosition.z)) {
        playerPosition = newPosition; // Update player position
    }
    if(!isPlayerOnGround()){
        newPosition.y -= gravity;
    }
    checkCollisions();
}

Block WorldState::getBlockAt(int x, int y, int z) const {
    // Calculate chunk coordinates
    int chunkX = x / 16;
    int chunkZ = z / 16;

    // Calculate block coordinates within the chunk
    int blockX = x % 16;
    int blockY = y;
    int blockZ = z % 16;

    // Ensure chunkX and chunkZ are within bounds
    if (chunkX >= 0 && chunkX < 5 && chunkZ >= 0 && chunkZ < 5) {
        // Get the chunk
        const Chunk& chunk = world[chunkX][0][chunkZ];

        // Ensure blockY is within bounds
        if (blockY >= 0 && blockY < 16) {
            return chunk.getBlock(blockX, blockY, blockZ); // Return the block
        }
    }

    // If out of bounds, return an air block
    return Block(0); // Air block
}
bool WorldState::isColliding(float x, float y, float z) {
    // Player bounding box (1x2x1 blocks)
    float playerWidth = 0.5f; // Half the player's width
    float playerHeight = 1.8f; // Player's height
    float playerDepth = 0.5f; // Half the player's depth

    // Check for collisions in all directions
    for (float dx = -playerWidth; dx <= playerWidth; dx += playerWidth) {
        for (float dy = 0; dy <= playerHeight; dy += playerHeight) {
            for (float dz = -playerDepth; dz <= playerDepth; dz += playerDepth) {
                int blockX = static_cast<int>(x + dx);
                int blockY = static_cast<int>(y + dy);
                int blockZ = static_cast<int>(z + dz);

                // Check if the block is solid
                Block block = getBlockAt(blockX, blockY, blockZ);
                if (block.getType() != 0) { // 0 = air (not solid)
                    return true; // Collision detected
                }
            }
        }
    }

    return false; // No collision
}

void WorldState::checkCollisions(){
        // Player bounding box (1x2x1 blocks)
        float playerWidth = 1.0f;
        float playerHeight = 2.0f;
        float playerDepth = 1.0f;
    
        // Check collisions in all directions
        if (isColliding(playerPosition.x + playerWidth / 2, playerPosition.y, playerPosition.z)) {
            playerPosition.x -= 0.1f; // Move back if colliding on the right
        }
        if (isColliding(playerPosition.x - playerWidth / 2, playerPosition.y, playerPosition.z)) {
            playerPosition.x += 0.1f; // Move back if colliding on the left
        }
        // if (isColliding(playerPosition.x, playerPosition.y + playerHeight, playerPosition.z)) {
        //     playerPosition.y -= 0.1f; // Move down if colliding above
        // }
        if (isColliding(playerPosition.x, playerPosition.y - playerHeight, playerPosition.z)) {
            playerPosition.y += 0.1f; // Move up if colliding down
        }
        if (isColliding(playerPosition.x, playerPosition.y, playerPosition.z + playerDepth / 2)) {
            playerPosition.z -= 0.1f; // Move back if colliding in front
        }
        if (isColliding(playerPosition.x, playerPosition.y, playerPosition.z - playerDepth / 2)) {
            playerPosition.z += 0.1f; // Move back if colliding behind
        }
    }
    
    bool WorldState::raycast(const ofVec3f& start, const ofVec3f& end, int& blockX, int& blockY, int& blockZ) {
        float stepSize = 0.01f; // Smaller step size = more accurate raycasting
        ofVec3f direction = (end - start).getNormalized();
        ofVec3f current = start;
    
        while (current.distance(start) < end.distance(start)) {
            // Convert world coordinates to block coordinates
            blockX = static_cast<int>(floor(current.x));
            blockY = static_cast<int>(floor(current.y));
            blockZ = static_cast<int>(floor(current.z));
    
            // Debug: Print the block coordinates being checked
            std::cout << "Checking block: (" << blockX << ", " << blockY << ", " << blockZ << ")" << std::endl;
    
            // Check if the block is solid
            Block block = getBlockAt(blockX, blockY, blockZ);
            if (block.getType() != 0) { // 0 = air
                return true; // Found a solid block
            }
    
            // Move along the ray
            current += direction * stepSize;
        }
    
        return false; // No solid block found
    }
void WorldState::mouseMoved(int x, int y) {
    if (!isMouseHidden) {
        // Hide the mouse cursor and reset its position to the center of the screen
        ofHideCursor();
        isMouseHidden = true;
        GLFWwindow* window = glfwGetCurrentContext();
        if (window) {
            glfwSetCursorPos(window, ofGetWidth() / 2, ofGetHeight() / 2);
        }
    }

    // Calculate mouse movement delta
    int deltaX = x - ofGetWidth() / 2;
    int deltaY = y - ofGetHeight() / 2;

    deltaX = -deltaX;

    // Rotate the camera based on mouse movement
    camera.rotate(deltaX, deltaY);

    // Reset the mouse position to the center of the screen
    GLFWwindow* window = glfwGetCurrentContext();
    if (window) {
        glfwSetCursorPos(window, ofGetWidth() / 2, ofGetHeight() / 2);
    }
}
void WorldState::drawHotbar() {
    // Switch to orthographic projection for 2D rendering
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); // Save the current projection matrix
    glLoadIdentity();
    gluOrtho2D(0, ofGetWidth(), ofGetHeight(), 0); // Set up 2D orthographic projection

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix(); // Save the current model-view matrix
    glLoadIdentity();

    // Disable depth testing for 2D rendering
    glDisable(GL_DEPTH_TEST);

    const int HOTBAR_SLOTS = 9; // Number of slots in the hotbar
    const int SLOT_SIZE = 64; // Size of each slot (in pixels)
    const int HOTBAR_WIDTH = HOTBAR_SLOTS * SLOT_SIZE; // Total width of the hotbar
    const int HOTBAR_HEIGHT = SLOT_SIZE; // Height of the hotbar

    // Calculate the position of the hotbar (centered at the bottom of the screen)
    int hotbarX = (ofGetWidth() - HOTBAR_WIDTH) / 2;
    int hotbarY = ofGetHeight() - HOTBAR_HEIGHT - 10; // 10 pixels above the bottom

    // Draw the hotbar background
    ofSetColor(100, 100, 100); // Gray background
    ofDrawRectangle(hotbarX, hotbarY, HOTBAR_WIDTH, HOTBAR_HEIGHT);

    // Draw each slot in the hotbar
    for (int i = 0; i < HOTBAR_SLOTS; ++i) {
        int slotX = hotbarX + i * SLOT_SIZE;
        int slotY = hotbarY;

        // Draw the slot border
        ofSetColor(0, 0, 0); // Black border
        ofNoFill();
        ofDrawRectangle(slotX, slotY, SLOT_SIZE, SLOT_SIZE);
        ofFill();

        // Draw the item in the slot (if any)
        ItemContainer& slot = inventory[18 + i]; // Hotbar slots are 18-26
        if (!slot.isEmpty()) {
            ofImage itemSprite = slot.getCurrentItem().getSprite();
            itemSprite.draw(slotX, slotY, SLOT_SIZE, SLOT_SIZE);

            // Draw the item count (if greater than 1)
            if (slot.getItemCount() > 1) {
                ofSetColor(255, 255, 255); // White text
                ofDrawBitmapString(ofToString(slot.getItemCount()), slotX + SLOT_SIZE - 20, slotY + SLOT_SIZE - 10);
            }
        }
    }

    // Draw the selected slot indicator
    int selectedSlotX = hotbarX + selectedHotbarSlot * SLOT_SIZE;
    ofSetColor(255, 255, 0); // Yellow border for selected slot
    ofNoFill();
    ofDrawRectangle(selectedSlotX, hotbarY, SLOT_SIZE, SLOT_SIZE);
    ofFill();

    // Restore the previous projection and model-view matrices
    glMatrixMode(GL_PROJECTION);
    glPopMatrix(); // Restore the previous projection matrix

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix(); // Restore the previous model-view matrix

    // Re-enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);
}

void WorldState::mousePressed(int x, int y, int button) {
    if (button == 0) { // Left click (break block)
        // Perform raycasting to determine which block the player is looking at
        ofVec3f rayStart = camera.getPosition();
        ofVec3f rayDirection = camera.getForwardDirection();
        ofVec3f rayEnd = rayStart + rayDirection * 10.0f; // Ray length of 10 units

        // Perform raycasting to find the block being looked at
        int blockX, blockY, blockZ;
        if (raycast(rayStart, rayEnd, blockX, blockY, blockZ)) {
            removeBlock(blockX, blockY, blockZ); // Break the block
        }
    } else if (button == 2) { // Right click (place block)
        // Get the selected item from the hotbar
        ItemContainer& selectedSlot = inventory[18 + selectedHotbarSlot];
        if (!selectedSlot.isEmpty()) {
            int blockType = selectedSlot.getCurrentItem().getItemNumber();

            // Perform raycasting to determine where to place the block
            ofVec3f rayStart = camera.getPosition();
            ofVec3f rayDirection = camera.getForwardDirection();
            ofVec3f rayEnd = rayStart + rayDirection * 10.0f; // Ray length of 10 units

            // Perform raycasting to find the block being looked at
            int blockX, blockY, blockZ;
            if (raycast(rayStart, rayEnd, blockX, blockY, blockZ)) {
                placeBlock(blockX, blockY, blockZ, Block(blockType)); // Place the block
            }
        }
    }
}
void WorldState::loadWorld() {
    const int CHUNK_SIZE = 16;
    const int WORLD_SIZE = 5; // 5x5 chunks

    // Resize the world to 5x5x5 chunks
    world.resize(WORLD_SIZE, std::vector<std::vector<Chunk>>(WORLD_SIZE, std::vector<Chunk>(WORLD_SIZE)));

    // Generate a flat world
    for (int cx = 0; cx < WORLD_SIZE; ++cx) {
        for (int cz = 0; cz < WORLD_SIZE; ++cz) {
            for (int x = 0; x < CHUNK_SIZE; ++x) {
                for (int z = 0; z < CHUNK_SIZE; ++z) {
                    // Set the ground layer (y = 4) to grass
                    world[cx][0][cz].setBlock(x, 4, z, Block(2)); // Grass
                    // Set the layers below (y = 0 to 3) to dirt
                    for (int y = 0; y < 4; ++y) {
                        world[cx][0][cz].setBlock(x, y, z, Block(3)); // Dirt
                    }
                    // Set the layers above (y = 5 to 15) to air
                    for (int y = 5; y < CHUNK_SIZE; ++y) {
                        world[cx][0][cz].setBlock(x, y, z, Block(0)); // Air
                    }
                }
            }
        }
    }
}

void WorldState::placeBlock(int x, int y, int z, Block block) {
    int chunkX = x / 16;
    int chunkY = y / 16;
    int chunkZ = z / 16;
    int blockX = x % 16;
    int blockY = y % 16;
    int blockZ = z % 16;

    if (chunkX >= 0 && chunkX < 5 && chunkY >= 0 && chunkY < 5 && chunkZ >= 0 && chunkZ < 5) {
        // Check if the block can be placed (e.g., not inside the player)
        if (!isColliding(x, y, z)) {
            // Find the selected slot in the hotbar (slots 18-26)
            int selectedSlot = 18; // Default to the first slot in the hotbar
            for (int i = 18; i < 27; ++i) {
                if (!inventory[i].isEmpty() && inventory[i].getCurrentItem().getItemNumber() == block.getType()) {
                    selectedSlot = i;
                    break;
                }
            }

            // Deduct one item from the hotbar
            if (!inventory[selectedSlot].isEmpty()) {
                inventory[selectedSlot].deductOne();

                // Place the block in the world
                world[chunkX][chunkY][chunkZ].setBlock(blockX, blockY, blockZ, block);
            }
        }
    }
}

void WorldState::removeBlock(int x, int y, int z) {
    int chunkX = x / 16;
    int chunkY = y / 16;
    int chunkZ = z / 16;
    int blockX = x % 16;
    int blockY = y % 16;
    int blockZ = z % 16;

    if (chunkX >= 0 && chunkX < 5 && chunkY >= 0 && chunkY < 5 && chunkZ >= 0 && chunkZ < 5) {
        Block block = world[chunkX][chunkY][chunkZ].getBlock(blockX, blockY, blockZ);
        if (block.getType() != 0) { // If not air
            // Add the block to the first available slot in the hotbar (slots 18-26)
            for (int i = 18; i < 27; ++i) {
                if (inventory[i].isEmpty() || (inventory[i].getCurrentItem().getItemNumber() == block.getType() && !inventory[i].isMaxed())) {
                    inventory[i].setCurrentItem(itemHandler->getItemFromNumber(block.getType()));
                    inventory[i].addOne();
                    break;
                }
            }

            // Set the block to air (remove it from the world)
            world[chunkX][chunkY][chunkZ].setBlock(blockX, blockY, blockZ, Block(0));
        }
    }
}

void WorldState::setColor(const Color& color) {
    glColor3ub(color.r, color.g, color.b); // Set the current drawing color
}

void WorldState::drawCube(float x, float y, float z, float size) {
    float halfSize = size / 2.0f;

    // Define the 8 vertices of the cube
    float vertices[8][3] = {
        {x - halfSize, y - halfSize, z - halfSize},
        {x + halfSize, y - halfSize, z - halfSize},
        {x + halfSize, y + halfSize, z - halfSize},
        {x - halfSize, y + halfSize, z - halfSize},
        {x - halfSize, y - halfSize, z + halfSize},
        {x + halfSize, y - halfSize, z + halfSize},
        {x + halfSize, y + halfSize, z + halfSize},
        {x - halfSize, y + halfSize, z + halfSize}
    };

    // Define the 6 faces of the cube using the vertices
    int faces[6][4] = {
        {0, 1, 2, 3}, // Front face
        {1, 5, 6, 2}, // Right face
        {5, 4, 7, 6}, // Back face
        {4, 0, 3, 7}, // Left face
        {3, 2, 6, 7}, // Top face
        {4, 5, 1, 0}  // Bottom face
    };

    // 🎨 Draw the filled cube first
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            glVertex3fv(vertices[faces[i][j]]);
        }
    }
    glEnd();

    // 🖊 Draw the outline (wireframe mode)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);  // Outline thickness
    glColor3f(0.0f, 0.0f, 0.0f);  // Black outline

    glBegin(GL_LINES);
    // Define the 12 edges of the cube
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Front face edges
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Back face edges
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Connecting edges
    };

    for (int i = 0; i < 12; ++i) {
        glVertex3fv(vertices[edges[i][0]]);
        glVertex3fv(vertices[edges[i][1]]);
    }
    glEnd();

    // Restore normal rendering mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
