#pragma once
#include "ofMain.h"

/**
 * @class StateButton
 * @brief Represents a button that allows the player to switch between different game states.
 */
class StateButton {
    private:
        ofRectangle collider; ///< Handles collision with the mouse cursor.
        ofImage buttonSprite; ///< Texture of the button.
        string targetState; ///< The state that the button navigates to.
        const int WIDTH = 80; ///< Width of the button.
        const int HEIGHT = 71; ///< Height of the button.
        ofSoundPlayer soundEffect; ///< Sound effect played when the button is clicked.
    public:
        /**
         * @brief Constructs a new StateButton object.
         * 
         * This constructor initializes a StateButton with a target state, position, and default dimensions.
         * It loads the button sprite and sound effect, and sets up the collider for mouse interaction.
         * 
         * @param dS The target state that the button will navigate to.
         * @param pX The x-coordinate of the button's position.
         * @param pY The y-coordinate of the button's position.
         */
        StateButton(string dS, int pX, int pY) {
            this->targetState = dS;
            this->buttonSprite.load("images/states/" + targetState + "StateButton.png");
            this->collider.setPosition(pX, pY);
            this->collider.setWidth(WIDTH);
            this->collider.setHeight(HEIGHT);
            this->soundEffect.load("audio/buttonClick.mp3");
        }

        /**
         * @brief Gets the target state of the button.
         * @return The target state.
         */
        string getTargetState() { return this->targetState; }

        /**
         * @brief Checks if the button is pressed based on mouse coordinates.
         * @param x The x-coordinate of the mouse.
         * @param y The y-coordinate of the mouse.
         * @return True if the button is pressed, false otherwise.
         */
        bool onPress(int x, int y) { return collider.inside(x, y); }

        /**
         * @brief Plays the button click sound effect.
         */
        void playSoundEffect() { this->soundEffect.play(); }

        /**
         * @brief Draws the button on the screen.
         */
        void draw() { this->buttonSprite.draw(collider.getPosition()); }
};