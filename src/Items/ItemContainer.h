#pragma once
#include "Item.h"

/**
 * @class ItemContainer
 * @brief Represents a container that holds an item and its count, with various utility methods for item management.
 */
class ItemContainer {
    private:
        int currentItemCount; ///< The current count of the item in the container.
        Item currentItem; ///< The current item in the container.

        bool mouseHovering; ///< Indicates whether the mouse is hovering over the container.
        ofImage hoverHighlighter; ///< Image used to highlight the container when the mouse is hovering over it.
        ofRectangle collider; ///< Rectangle representing the container's position and size for collision detection.
    public:
        // Constructors

        /**
         * @brief Default constructor. Initializes an empty ItemContainer.
         */
        ItemContainer(){};

        /**
         * @brief Constructs an ItemContainer at the specified coordinates.
         * @param pX Horizontal coordinate.
         * @param pY Vertical coordinate.
         */
        ItemContainer(int pX, int pY);

        // Getters

        /**
         * @brief Gets the current item count.
         * @return The current item count.
         */
        int getItemCount() { return this->currentItemCount; }

        /**
         * @brief Checks if the mouse is hovering over the container.
         * @return True if the mouse is hovering, false otherwise.
         */
        bool isMouseHovering() { return this->mouseHovering; } 

        /**
         * @brief Checks if the container is empty.
         * @return True if the container is empty, false otherwise.
         */
        bool isEmpty() { return this->currentItem.getItemNumber() == 0;}

        /**
         * @brief Checks if the container is full.
         * @return True if the container is full, false otherwise.
         */
        bool isMaxed() { return this->getItemCount() == this->getCurrentItem().getMaxStack(); }

        /**
         * @brief Checks if adding a specified amount would exceed the container's max stack size.
         * @param amount The amount to add.
         * @return True if the container would be maxed after adding the amount, false otherwise.
         */
        bool isMaxedAfter(int amount) { return this->getItemCount() + amount > this->getCurrentItem().getMaxStack(); }

        /**
         * @brief Checks if the current item is a tool.
         * @return True if the item is a tool, false otherwise.
         */
        bool isTool() { return this->currentItem.getMaxStack() == 1; } // Simplistic checker. Disables the ability to add items that have a max stack of 1 that aren't tools. 

        /**
         * @brief Gets the current item.
         * @return The current item.
         */
        Item getCurrentItem() { return this->currentItem; }
        
        // Setters and useful methods

        /**
         * @brief Sets the item count.
         * @param newCount The new item count.
         */
        void setItemCount(int newCount) { this->currentItemCount = newCount; }

        /**
         * @brief Sets the current item.
         * @param newItem The new item.
         */
        void setCurrentItem(Item newItem) { this->currentItem = newItem; }

        /**
         * @brief Sets the position of the container.
         * @param x The horizontal coordinate.
         * @param y The vertical coordinate.
         */
        void setPos(int x, int y) { this->collider.setPosition(x,y); }

        /**
         * @brief Increases the item count by one.
         */
        void addOne() { this->currentItemCount++;}

        /**
         * @brief Decreases the item count by one. If the count reaches zero, the container is emptied.
         */
        void deductOne() { this->currentItemCount--; if (currentItemCount <= 0) empty(); }

        /**
         * @brief Empties the container, setting the item to air and the count to zero.
         */
        void empty() { this->currentItem.setToAir(); this->currentItemCount = 0; }

        // Swapping logic methods

        /**
         * @brief Checks if the mouse has entered the container's area.
         * @param x The horizontal coordinate of the mouse.
         * @param y The vertical coordinate of the mouse.
         */
        void mouseEntered(int x, int y) { this->collider.inside(x,y) ? this->mouseHovering = true : this->mouseHovering = false; }

        /**
         * @brief Handles left mouse click events for swapping items with the player's container.
         * @param x The horizontal coordinate of the mouse.
         * @param y The vertical coordinate of the mouse.
         * @param playerContainer The player's item container.
         */
        void leftMouseClicked(int x, int y, ItemContainer& playerContainer) { if (isMouseHovering()) leftSwapWith(playerContainer); }

        /**
         * @brief Handles right mouse click events for swapping items with the player's container.
         * @param x The horizontal coordinate of the mouse.
         * @param y The vertical coordinate of the mouse.
         * @param playerContainer The player's item container.
         */
        void rightMouseClicked(int x, int y, ItemContainer& playerContainer) { if (isMouseHovering()) rightSwapWith(playerContainer); }

        /**
         * @brief Swaps items with the player's container using left mouse click logic.
         * @param playerContainer The player's item container.
         */
        void leftSwapWith(ItemContainer& playerContainer);

        /**
         * @brief Swaps items with the player's container using right mouse click logic.
         * @param playerContainer The player's item container.
         */
        void rightSwapWith(ItemContainer& playerContainer);

        /**
         * @brief Draws the container, highlighting it if the mouse is hovering over it.
         */
        void draw(); 
};