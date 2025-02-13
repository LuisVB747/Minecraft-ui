#pragma once
#include "State.h"

/**
 * @class FurnaceState
 * @brief Represents the state of the game when the player is interacting with a furnace.
 */
class FurnaceState : public State {
    private:
        int fuel; ///< The current fuel level in the furnace.
        ItemContainer fuelContainer; ///< Container that holds the fuel.
        ItemContainer burningContainer; ///< Container that holds the smeltable item.
        ItemContainer resultContainer; ///< Container that holds the resulting item.
        ItemHandler* instantiator; ///< Pointer to the item handler for item creation.
        vector<int> smeltableItems; ///< Holds the numbers of all smeltable items.
    public:
        /**
         * @brief Constructs a FurnaceState object with a player and an item handler pointer.
         * @param player Player pointer.
         * @param instantiator Item handler pointer.
         */
        FurnaceState(Player* player, ItemHandler* instantiatr);

        /**
         * @brief Checks if an item is smeltable by iterating through smeltableItems.
         * @param itm The item to check.
         * @return True if the item is smeltable, false otherwise.
         */
        bool isItemSmeltable(Item itm) {
            for (int itemNum : this->smeltableItems) { if (itm.getItemNumber() == itemNum) return true; }
            return false;
        }

        /**
         * @brief Checks if conditions are met for smelting.
         * @return True if the conditions are met, false otherwise.
         */
        bool canSmelt();

        /**
         * @brief Returns the resulting item number of the passed in smeltable item.
         * @param itm The smeltable item.
         * @return The item number of the resulting item.
         */
        int getResultantItemNumber(Item itm);

        /**
         * @brief Smelts the item in the burning container, producing the result in the result container.
         */
        void smelt();

        /**
         * @brief Adds all of the smeltable item numbers to the smeltableItems vector.
         */
        void addSmeltableItems();

        /**
         * @brief Updates the state. Mandatory implementation.
         */
        void update();

        /**
         * @brief Draws the furnace state on the screen.
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
         * @brief Handles key press events. Mandatory unused implementation.
         * @param key The key that was pressed.
         */
        void keyPressed(int key) {};
};