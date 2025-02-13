#pragma once
#include "ofMain.h" 

/**
 * @class Item
 * @brief Represents an item in the game with various properties such as item number, stack size, fuel level, sprite, and name.
 */
class Item {
    private:
        int itemNumber; ///< Unique identifier for the item.
        int maxStack; ///< Maximum stack size for the item.
        int fuelLevel; ///< Fuel level indicating how much the item burns in a furnace.
        ofImage sprite; ///< Sprite image representing the item.
        string name; ///< Display name of the item.
    public:
        /**
         * @brief Constructs an Item object with specified properties.
         * @param iN Unique item identifier. Conventionally itemNumber is greater than 0.
         * @param mS Maximum amount of an item that any ItemContainer can hold. Conventionally the stack sizes are 1, 16, and 64.
         * @param fL Fuel level indicating how much the item burns in a furnace. One fuel equals one smelted item. Most items have a fuel level of 0.
         * @param spr Sprite image that will be used in the draw() method. The sprite must be 64x64 pixels to fit in the container.
         * @param iNa Display name for the item.
         */
        Item(int iN, int mS, int fL, ofImage spr, string iNa) {
            this->itemNumber = iN;
            this->maxStack = mS;
            this->fuelLevel = fL;
            this->sprite = spr;
            this->name = iNa;
        }

        /**
         * @brief Default constructor. Initializes the item as an air (empty) item.
         */
        Item() { this->setToAir(); } 

        // Getters

        /**
         * @brief Gets the unique item number.
         * @return The item number.
         */
        int getItemNumber() { return this->itemNumber; }

        /**
         * @brief Gets the maximum stack size.
         * @return The maximum stack size.
         */
        int getMaxStack() { return this->maxStack; } 

        /**
         * @brief Gets the fuel level.
         * @return The fuel level.
         */
        int getFuelLevel() { return this->fuelLevel; }

        /**
         * @brief Gets the sprite image.
         * @return The sprite image.
         */
        ofImage getSprite() { return this->sprite;}

        /**
         * @brief Gets the display name.
         * @return The display name.
         */
        string getName() { return this->name; }

        // Setters

        /**
         * @brief Sets the item to air, making it empty.
         */
        void setToAir() {
            this->itemNumber = 0;
            this->maxStack = 1;
            this->fuelLevel = 0;
            ofImage airSpr;
            airSpr.load("images/sprites/sprites.png");
            airSpr.crop(0,0,64,64);
            this->sprite = airSpr;
            this->name = "air";
        }

        // Useful operators that enable direct comparison of items.

        /**
         * @brief Equality operator to compare two items.
         * @param other The other item to compare with.
         * @return True if the items have the same item number, false otherwise.
         */
        bool operator==(const Item& other) const { return this->itemNumber == other.itemNumber; }

        /**
         * @brief Inequality operator to compare two items.
         * @param other The other item to compare with.
         * @return True if the items have different item numbers, false otherwise.
         */
        bool operator!=(const Item& other) const { return this->itemNumber != other.itemNumber; }
};