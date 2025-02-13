#pragma once
#include "State.h"

/**
 * @class ChestState
 * @brief Represents the state of the game when the player is interacting with a chest.
 */
class ChestState : public State {
    private:
        vector<ItemContainer> chestInventory; ///< An array of 27 ItemContainers representing the chest's inventory.
    public:
        /** 
         * @brief Constructs a ChestState object with a player pointer.
         * @param player Player pointer.
         */
        ChestState(Player* player);

        /**
         * @brief Adds items to the first available space in the chest.
         * @param itm The item to add.
         * @param count The count of the item to add.
         */
        void addItem(Item itm, int count); 

        /**
         * @brief Adds items to the specified slot in the chest.
         * @param itm The item to add.
         * @param count The count of the item to add.
         * @param slot The slot index to add the item to.
         */
        void addItem(Item itm, int count, int slot);

        /**
         * @brief Updates the state. Mandatory unused implementation.
         */
        void update(){}; 

        /**
         * @brief Draws the chest state on the screen.
         */
        void draw(); 

        /**
         * @brief Handles key press events. Mandatory unused implementation.
         * @param key The key that was pressed.
         */
        void keyPressed(int key){}

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
};