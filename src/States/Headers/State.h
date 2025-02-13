#pragma once
#include "Player.h"

/**
 * @class State
 * @brief Abstract base class representing a game state.
 */
class State {
    private:
        Player* player; ///< Pointer to the player object.
    public:
        ofImage background; ///< Background image for the state. Should be 704x668 pixels.

        /**
         * @brief Constructs a State object with a player pointer.
         * @param plyr Player pointer.
         */
        State(Player* plyr){ this->player = plyr;};

        /**
         * @brief Gets the player pointer.
         * @return The player pointer.
         */
        Player* getPlayer() { return this->player; }

        /**
         * @brief Updates the state. Pure virtual function to be implemented by derived classes.
         */
        virtual void update() = 0;

        /**
         * @brief Draws the state. Pure virtual function to be implemented by derived classes.
         */
        virtual void draw() = 0;

        /**
         * @brief Handles key press events. Pure virtual function to be implemented by derived classes.
         * @param key The key that was pressed.
         */
        virtual void keyPressed(int key) = 0;

        /**
         * @brief Handles mouse movement events.
         * @param x The x-coordinate of the mouse.
         * @param y The y-coordinate of the mouse.
         */
        virtual void mouseMoved(int x, int y) { 
            for (auto& slot : this->getPlayer()->getInventory()) { slot.mouseEntered(x,y); }
            player->getCursorContainer().setPos(x-32,y-32);
        };

        /**
         * @brief Handles mouse press events.
         * @param x The x-coordinate of the mouse.
         * @param y The y-coordinate of the mouse.
         * @param button The mouse button that was pressed. 0 for left click, 2 for right click.
         */
        virtual void mousePressed(int x, int y, int button) {
            if (button == 0) for (auto& slot : player->getInventory()) { slot.leftMouseClicked(x,y,player->getCursorContainer()); }
            if (button == 2) for (auto& slot : player->getInventory()) { slot.rightMouseClicked(x,y,player->getCursorContainer()); }
        }
};