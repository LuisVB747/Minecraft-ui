#include "WorldState.h"
#include <GL/gl.h> // Include OpenGL headers
#include <GL/glu.h> // Include GLU utilities
#include <GLFW/glfw3.h>

WorldState::WorldState(Player* player, ItemHandler* itemHandler) : State(player) {
    this->itemHandler = itemHandler;
    // Initialize player position and camera
    playerPosition.set(40, 10, 40); // Start the player above the ground
    playerYaw = 0.0f; // Initial horizontal rotation
    playerPitch = 0.0f; // Initial vertical rotation
    camAccel = 0;
    generalAccel = 0;
    lastx = 0;
    lasty = 0;
    currx = 0;
    curry = 0;
    // Initialize the camera
    cam.setNearClip(0.1f); // Set near clipping plane
    cam.setFarClip(1000.0f); // Set far clipping plane
    ofHideCursor(); // Hide the mouse cursor
    loadWorld(); // Load or generate the world
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

    // Draw each face of the cube
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            glVertex3fv(vertices[faces[i][j]]);
        }
    }
    glEnd();
}

void WorldState::update() {
    playerYaw -= camAccel;
    playerPitch -= camAccel;
    camAccel = 0;
}

void WorldState::draw() {
    ofEnableDepthTest(); // Enable depth testing for 3D rendering

    // Set the camera position and orientation
    cam.begin();
    cam.setPosition(playerPosition); // Set camera to player's position
    cam.rotateDeg(playerPitch, 1, 0, 0); // Rotate vertically (up/down)
    cam.rotateDeg(playerYaw, 0, 1, 0); // Rotate horizontally (left/right)

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

    cam.end();
    ofDisableDepthTest(); // Disable depth testing
    lastx= currx;
    lasty = curry;
}


void WorldState::keyPressed(int key) {
        float moveSpeed = 1.0f; // Adjust movement speed as needed
    
        if (key == 'w' || key == 'W') { // Move forward
            playerPosition.x -= moveSpeed * sin(ofDegToRad(playerYaw));
            playerPosition.z -= moveSpeed * cos(ofDegToRad(playerYaw));
        }
        if (key == 's' || key == 'S') { // Move backward
            playerPosition.x += moveSpeed * sin(ofDegToRad(playerYaw));
            playerPosition.z += moveSpeed * cos(ofDegToRad(playerYaw));
        }
        if (key == 'a' || key == 'A') { // Move left
            playerPosition.x -= moveSpeed * cos(ofDegToRad(playerYaw));
            playerPosition.z += moveSpeed * sin(ofDegToRad(playerYaw));
        }
        if (key == 'd' || key == 'D') { // Move right
            playerPosition.x += moveSpeed * cos(ofDegToRad(playerYaw));
            playerPosition.z -= moveSpeed * sin(ofDegToRad(playerYaw));
        }
        if (key == ' ') { // Move up (jump)
            playerPosition.y += moveSpeed;

        }
        if (key == OF_KEY_CONTROL) { // Move down (crouch)
            playerPosition.y -= moveSpeed;
        }
    }


    void WorldState::mouseMoved(int x, int y) {
        float sensitivity = 0.001f; // Adjust mouse sensitivity as needed
    
        // Calculate mouse movement delta
        int deltaX = x - lastx;
        int deltaY = y - lasty;
        currx = x;
        curry = y;
    
        // Update player rotation
        playerYaw += deltaX * sensitivity;  // Horizontal rotation
        playerPitch -= deltaY * sensitivity; // Vertical rotation
    
        // Clamp vertical rotation to avoid flipping
        playerPitch = ofClamp(playerPitch, -90.0f, 90.0f);
    
        // Reset mouse position to the center of the screen using GLFW
        GLFWwindow* window = glfwGetCurrentContext();
        if (window) {
            glfwSetCursorPos(window, ofGetWidth() / 2, ofGetHeight() / 2);
        }
    }
    
void WorldState::mousePressed(int x, int y, int button) {
    // Handle mouse press events (e.g., place/remove blocks)
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

    // Debug: Print the number of non-air blocks in each chunk
    for (int cx = 0; cx < WORLD_SIZE; ++cx) {
        for (int cz = 0; cz < WORLD_SIZE; ++cz) {
            int nonAirBlocks = 0;
            for (int x = 0; x < CHUNK_SIZE; ++x) {
                for (int y = 0; y < CHUNK_SIZE; ++y) {
                    for (int z = 0; z < CHUNK_SIZE; ++z) {
                        if (world[cx][0][cz].getBlock(x, y, z).getType() != 0) {
                            nonAirBlocks++;
                        }
                    }
                }
            }
            std::cout << "Chunk (" << cx << ", 0, " << cz << ") has " << nonAirBlocks << " non-air blocks." << std::endl;
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
        world[chunkX][chunkY][chunkZ].setBlock(blockX, blockY, blockZ, block);
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
            getPlayer()->addItem(itemHandler->getItemFromNumber(block.getType()), 1); // Add to inventory
            world[chunkX][chunkY][chunkZ].setBlock(blockX, blockY, blockZ, Block(0)); // Set to air
        }
    }
}