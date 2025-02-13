#pragma once
#include "State.h"

/**
 * @class CraftingState
 * @brief Represents the state of the game when the player is interacting with a crafting table.
 */
class CraftingState : public State {
    private:
        vector<ItemContainer> craftingGrid; ///< A 3x3 grid of ItemContainers representing the crafting grid.
        ItemContainer resultContainer; ///< The container that holds the result of the crafting recipe.
        ItemHandler* instantiator; ///< Pointer to the item handler for item creation.
    public:
        /**
         * @brief Constructs a CraftingState object with a player pointer and an item handler.
         * @param player Player pointer.
         * @param instantiator Item handler pointer.
         */
        CraftingState(Player* player, ItemHandler* instantiator);

        /**
         * @brief Handles crafting logic, combining items in the crafting grid to produce a result.
         */
        void craft();

        /**
         * @brief Holds all of the recipes and returns the crafted item and its count based on the crafting grid.
         * @param grid A vector of item numbers representing the crafting grid.
         * @return A pair containing the crafted item and its count.
         */
        pair<Item,int> getItemFromRecipie(vector<int> grid);

        /**
         * @brief Helper function that snaps the ingredients to the upper left corner of the grid.
         * @param grid A vector of item numbers representing the crafting grid.
         */
        void standarizeGrid(vector<int>& grid);

        /**
         * @brief Updates the state. Mandatory unused implementation.
         */
        void update(){}; 

        /**
         * @brief Draws the crafting state on the screen.
         */
        void draw(); 

        /**
         * @brief Handles key press events.
         * @param key The key that was pressed.
         */
        void keyPressed(int key) { if (key == 'C' || key == 'c') craft(); }

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