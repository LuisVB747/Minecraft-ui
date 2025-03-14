#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    this->instantiator = new ItemHandler();
    this->player = new Player();
    this->chestState = new ChestState(player);
    this->craftingState = new CraftingState(player, instantiator);
    this->furnaceState = new FurnaceState(player, instantiator);
    this->generatorState = new GeneratorState(player, instantiator);
    this->armorState = new ArmorState(player, instantiator);
    this->worldState = new WorldState(player, instantiator);
    this->bossState = new BossState(player, instantiator, this->armorState);

    this->relaxingMusic.load("audio/miceOnVenus.mp3");
    this->relaxingMusic.play();

    giveItems();
    this->currentState = chestState;


}

//--------------------------------------------------------------
void ofApp::update() {
    if (!relaxingMusic.isPlaying()) relaxingMusic.play();
    currentState->update();
}

//--------------------------------------------------------------
void ofApp::draw() {


    // Draw the current state (e.g., chest, crafting, furnace)
    currentState->draw();
}

//--------------------------------------------------------------
void ofApp::setColor(const ofColor& color) {
    glColor3ub(color.r, color.g, color.b); // Set the current drawing color
}

//--------------------------------------------------------------
void ofApp::drawCube(float x, float y, float z, float size) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    currentState->mousePressed(x, y, button);
    if (button == 0) {
        // Iterate through StateButtons
        for (auto stateButton : player->getStateButtons()) {
            if (stateButton.onPress(x, y)) {
                if (stateButton.getTargetState() == "chest") {
                    this->currentState = chestState;
                } else if (stateButton.getTargetState() == "crafting") {
                    this->currentState = craftingState;
                } else if (stateButton.getTargetState() == "furnace") {
                    this->currentState = furnaceState;
                } else if (stateButton.getTargetState() == "generator") {
                    this->currentState = generatorState;
                } else if (stateButton.getTargetState() == "Armor") {
                    this->currentState = armorState;
                } else if(stateButton.getTargetState() == "world"){
                    this->currentState = worldState;
                }
                else if(stateButton.getTargetState() == "boss"){
                    this->currentState = bossState;
                }
                stateButton.playSoundEffect();
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'B' || key == 'b') {  // Check if 'B' or 'b' is pressed
        this->player->addItem(instantiator->getItemFromNumber(40), 5);
        this->player->addItem(instantiator->getItemFromNumber(41), 3);
        this->player->addItem(instantiator->getItemFromNumber(37), 1);
        this->player->addItem(instantiator->getItemFromNumber(62), 1);
    }
    if (key == 'E' || key == 'e') {  // Check if 'E' or 'e' is pressed
        this->player->addItem(instantiator->getItemFromNumber(50), 64);
        this->player->addItem(instantiator->getItemFromNumber(42), 5);
        this->player->addItem(instantiator->getItemFromNumber(18), 1);
        this->player->addItem(instantiator->getItemFromNumber(8), 1);
        this->player->addItem(instantiator->getItemFromNumber(23), 1);
        this->player->addItem(instantiator->getItemFromNumber(13), 1);
        this->player->addItem(instantiator->getItemFromNumber(28), 1);
    }
    if (key == 'i' || key == 'I') { // Exit WorldState and return to ChestState
        resetOpenGLStates(); // Reset OpenGL states
        this->currentState = chestState; // Transition back to ChestState
        ofShowCursor(); // Show the cursor
    }
    currentState->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::giveItems() {
    this->player->addItem(instantiator->getItemFromNumber(55), 1, 26);
    this->chestState->addItem(instantiator->getItemFromNumber(2), 4);
    this->chestState->addItem(instantiator->getItemFromNumber(5), 1);
    this->chestState->addItem(instantiator->getItemFromNumber(10), 1);
    this->chestState->addItem(instantiator->getItemFromNumber(15), 1);
    this->chestState->addItem(instantiator->getItemFromNumber(20), 1);
    this->chestState->addItem(instantiator->getItemFromNumber(25), 1);

    // Testing
    this->player->addItem(instantiator->getItemFromNumber(62), 1);
    this->player->addItem(instantiator->getItemFromNumber(63), 1);
    this->player->addItem(instantiator->getItemFromNumber(66), 1);
    this->player->addItem(instantiator->getItemFromNumber(67), 1);
    this->player->addItem(instantiator->getItemFromNumber(70), 1);
    this->player->addItem(instantiator->getItemFromNumber(71), 1);
    this->player->addItem(instantiator->getItemFromNumber(74), 1);
    this->player->addItem(instantiator->getItemFromNumber(75), 1);
    // this->chestState->addItem(instantiator->getItemFromNumber(79), 1);
    // this->chestState->addItem(instantiator->getItemFromNumber(44), 1);
    // this->chestState->addItem(instantiator->getItemFromNumber(46), 1);
    // this->chestState->addItem(instantiator->getItemFromNumber(52), 1);
    // this->chestState->addItem(instantiator->getItemFromNumber(53), 1);
    // this->chestState->addItem(instantiator->getItemFromNumber(54), 1);
    // this->chestState->addItem(instantiator->getItemFromNumber(55), 1);
    // this->chestState->addItem(instantiator->getItemFromNumber(56), 1);
    // this->chestState->addItem(instantiator->getItemFromNumber(40), 6);
    // this->chestState->addItem(instantiator->getItemFromNumber(37), 6);
    // this->chestState->addItem(instantiator->getItemFromNumber(41), 6);

}

void ofApp::resetOpenGLStates() {
    // // Reset OpenGL states to defaults
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    // glEnable(GL_DEPTH_TEST); // Re-enable depth testing (if disabled)
    // ofSetColor(255, 255, 255); // Reset color to white
    // ofFill(); // Reset fill mode
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