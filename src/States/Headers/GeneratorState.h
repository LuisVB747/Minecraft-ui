#pragma once
#include "State.h"

/**
 * @class GeneratorState
 * @brief Represents the state of the game when the player is interacting with a generator.
 */
class GeneratorState : public State {
    private:
        ItemContainer toolContainer; ///< Container that holds the tool to be used.
        ItemContainer resultContainer; ///< Container that holds the resulting item.
        ItemHandler* instantiator; ///< Pointer to the item handler for item creation.
        vector<vector<int>> lootTables; ///< Loot tables for all tools that fit into the toolContainer.
    public:
        /**
         * @brief Constructs a GeneratorState object with a player and an item handler pointer.
         * @param player Player pointer.
         * @param instantiator Item handler pointer.
         */
        GeneratorState(Player* player, ItemHandler* instantiatr);

        /**
         * @brief Generates an item based on the tool inside the toolContainer.
         */
        void generateItem();

        /**
         * @brief Creates loot tables for all tools that fit into the toolContainer.
         */
        void createLootTables();

        /**
         * @brief Updates the state. Mandatory implementation.
         */
        void update(){}; 

        /**
         * @brief Draws the generator state on the screen.
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
         * @brief Handles key press events. Tries to generate an item when the 'g' key is pressed.
         * @param key The key that was pressed.
         */
        void keyPressed(int key) { if (key == 'g') generateItem(); }; 
};