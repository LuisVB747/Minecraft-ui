#pragma once

#include "ofMain.h"
#include "Player.h"
#include "State.h"
#include "ChestState.h"
#include "CraftingState.h"
#include "FurnaceState.h"
#include "GeneratorState.h"
#include "ArmorState.h"
#include "WorldState.h"
#include <GL/gl.h> // Include OpenGL headers
#include <GL/glu.h> // Include GLU utilities (optional)

using namespace std;

/**
 * @class ofApp
 * @brief Main application class that handles the game setup, update, and rendering.
 */
class ofApp : public ofBaseApp {
public:
    Player* player; ///< Pointer to the player object.
    ItemHandler* instantiator; ///< Pointer to the item handler for item creation.
    State* currentState; ///< Pointer to the current game state.
    ChestState* chestState; ///< Pointer to the chest state.
    CraftingState* craftingState; ///< Pointer to the crafting state.
    FurnaceState* furnaceState; ///< Pointer to the furnace state.
    GeneratorState* generatorState; ///< Pointer to the generator state.
    ArmorState* armorState; ///< Pointer to the armor state.
    WorldState* worldState; ///< Pointer to the world state.

    ofSoundPlayer relaxingMusic; ///< Sound player for background music.
    ofEasyCam cam; ///< Camera for 3D navigation.

    /**
     * @brief Sets up the game, initializing all necessary components.
     */
    void setup();

    /**
     * @brief Updates the game state.
     */
    void update();

    /**
     * @brief Draws the game elements on the screen.
     */
    void draw();

    /**
     * @brief Handles mouse movement events.
     * @param x The x-coordinate of the mouse.
     * @param y The y-coordinate of the mouse.
     */
    void mouseMoved(int x, int y);

    /**
     * @brief Handles mouse press events.
     * @param x The x-coordinate of the mouse.
     * @param y The y-coordinate of the mouse.
     * @param button The mouse button that was pressed.
     */
    void mousePressed(int x, int y, int button);

    /**
     * @brief Handles key press events.
     * @param key The key that was pressed.
     */
    void keyPressed(int key);

    /**
     * @brief Gives items to the player and/or the chest.
     */
    void giveItems();

private:
    /**
     * @brief Sets the current drawing color.
     * @param color The color to set.
     */
    void setColor(const ofColor& color);

    /**
     * @brief Draws a cube at the specified position.
     * @param x The x-coordinate of the cube's center.
     * @param y The y-coordinate of the cube's center.
     * @param z The z-coordinate of the cube's center.
     * @param size The size of the cube.
     */
    void drawCube(float x, float y, float z, float size);

    //--UNUSED--//
    void keyReleased(int key);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};