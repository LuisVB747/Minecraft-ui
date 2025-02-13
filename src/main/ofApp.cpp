#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup() {
    this->instantiator = new ItemHandler();
    this->player = new Player();
    this->chestState = new ChestState(player);
    this->craftingState = new CraftingState(player,instantiator);
    this->furnaceState = new FurnaceState(player,instantiator);
    this->generatorState= new GeneratorState(player,instantiator);

    this->relaxingMusic.load("audio/miceOnVenus.mp3");
    this->relaxingMusic.play();

    giveItems();
    this->currentState = chestState;
}

/**
 * Handles mouse press events and manages state transitions.
 * 
 * This method is called whenever a mouse button is pressed. It delegates the event to the current state's
 * mousePressed method and checks if the left mouse button (button 0) was pressed. If so, it iterates through
 * the StateButtons and checks if any button was pressed. If a button is pressed, it changes the current state
 * to the target state of the button and plays the button's sound effect.
 * 
 * Basics of the state machine:
 * - The state machine consists of different states (e.g., "chest", "crafting", "furnace").
 * - Transitions between states occur based on user interactions with StateButton objects.
 * - Each state can have its own behavior and actions.
 * - The current state determines the system's behavior at any given time.
 * 
 * @param x The x-coordinate of the mouse cursor.
 * @param y The y-coordinate of the mouse cursor.
 * @param button The mouse button that was pressed (0 for left button, 2 for right button).
 */
void ofApp::mousePressed(int x, int y, int button) {
    currentState->mousePressed(x,y,button);
    if (button == 0) {
        // Iterate through StateButtons
        for (auto stateButton : player->getStateButtons()) {
            if (stateButton.onPress(x,y)) {
                if (stateButton.getTargetState() == "chest") {
                    this->currentState = chestState;
                }
                else if (stateButton.getTargetState() == "crafting") {
                    this->currentState = craftingState;
                }
                else if (stateButton.getTargetState() == "furnace") {
                    this->currentState = furnaceState;
                }
                else if (stateButton.getTargetState() == "generator") {
                    this->currentState = generatorState;
                }
                stateButton.playSoundEffect();
            }
        }
    }
}
void ofApp::update() { 
    if (!relaxingMusic.isPlaying()) relaxingMusic.play();
        currentState->update();
    }
void ofApp::draw() { currentState->draw();}
void ofApp::mouseMoved(int x, int y) { currentState->mouseMoved(x,y); }
void ofApp::keyPressed(int key) { currentState->keyPressed(key); }

// Helper function that gives the player, or the chest, items.
void ofApp::giveItems() {
    this->player->addItem(instantiator->getItemFromNumber(55), 1, 26);
    this->chestState->addItem(instantiator->getItemFromNumber(2), 4);
}



//------------------UNUSED--------------------------------------
void ofApp::keyReleased(int key) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}