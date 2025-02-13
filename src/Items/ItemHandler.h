#pragma once
#include "Item.h"

/**
 * @class ItemHandler
 * @brief Instantiator class that facilitates item creation and holds an array of all possible items.
 */
class ItemHandler {
    private:
        ofImage sheet; ///< The sprite sheet containing all item sprites.
        vector<Item> itemList; ///< List of all possible items.
    public:
        /**
         * @brief Helper function that returns the sprite given its row and column coordinates on the sprite sheet.
         * @param col The column coordinate on the sprite sheet.
         * @param row The row coordinate on the sprite sheet.
         * @return The sprite image.
         */
        ofImage getSpriteFromSheet(int col, int row) {
            ofImage sprite;
            sprite.cropFrom(sheet, col * 64, row * 64, 64, 64);
            return sprite;
        }

        /**
         * @brief Returns the item at the specified index.
         * @param itemNum The index of the item in the itemList.
         * @return The item at the specified index. If the index is out of bounds, returns an air item.
         */
        Item getItemFromNumber(int itemNum) {
            if (itemNum < 0 || itemNum >= (int)this->itemList.size()) { return Item(); }
            return itemList[itemNum];
        }

        /**
         * @brief Constructor that initializes the item handler by loading the sprite sheet and creating all possible items.
         */
        ItemHandler() {
            sheet.load("images/sprites/sprites.png");
            itemList.push_back(Item(0, 1, 0, getSpriteFromSheet(0, 0), "air"));

            itemList.push_back(Item(1, 64, 0, getSpriteFromSheet(2, 0), "Dirt"));
            itemList.push_back(Item(2, 64, 4, getSpriteFromSheet(15, 0), "Log"));
            itemList.push_back(Item(3, 64, 1, getSpriteFromSheet(4, 0), "Plank"));
            itemList.push_back(Item(4, 64, 1, getSpriteFromSheet(8, 13), "Sticks"));

            itemList.push_back(Item(5, 1, 1, getSpriteFromSheet(5, 15), "Wooden Pickaxe"));
            itemList.push_back(Item(6, 1, 0, getSpriteFromSheet(6, 15), "Stone Pickaxe"));
            itemList.push_back(Item(7, 1, 0, getSpriteFromSheet(7, 15), "Iron Pickaxe"));
            itemList.push_back(Item(8, 1, 0, getSpriteFromSheet(8, 15), "Diamond Pickaxe"));
            itemList.push_back(Item(9, 1, 0, getSpriteFromSheet(9, 15), "Gold Pickaxe"));
            itemList.push_back(Item(10, 1, 1, getSpriteFromSheet(12, 14), "Wooden Shovel"));
            itemList.push_back(Item(11, 1, 0, getSpriteFromSheet(13, 14), "Stone Shovel"));
            itemList.push_back(Item(12, 1, 0, getSpriteFromSheet(14, 14), "Iron Shovel"));
            itemList.push_back(Item(13, 1, 0, getSpriteFromSheet(15, 14), "Diamond Shovel"));
            itemList.push_back(Item(14, 1, 0, getSpriteFromSheet(16, 14), "Gold Shovel"));
            itemList.push_back(Item(15, 1, 1, getSpriteFromSheet(19, 13), "Wooden Sword"));
            itemList.push_back(Item(16, 1, 0, getSpriteFromSheet(20, 13), "Stone Sword"));
            itemList.push_back(Item(17, 1, 0, getSpriteFromSheet(21, 13), "Iron Sword"));
            itemList.push_back(Item(18, 1, 0, getSpriteFromSheet(22, 13), "Diamond Sword"));
            itemList.push_back(Item(19, 1, 0, getSpriteFromSheet(0, 14), "Gold Sword"));
            itemList.push_back(Item(20, 1, 1, getSpriteFromSheet(21, 15), "Wooden Axe"));
            itemList.push_back(Item(21, 1, 0, getSpriteFromSheet(22, 15), "Stone Axe"));
            itemList.push_back(Item(22, 1, 0, getSpriteFromSheet(0, 16), "Iron Axe"));
            itemList.push_back(Item(23, 1, 0, getSpriteFromSheet(1, 16), "Diamond Axe"));
            itemList.push_back(Item(24, 1, 0, getSpriteFromSheet(2, 16), "Gold Axe"));
            itemList.push_back(Item(25, 1, 1, getSpriteFromSheet(14, 16), "Wooden Hoe"));
            itemList.push_back(Item(26, 1, 0, getSpriteFromSheet(15, 16), "Stone Hoe"));
            itemList.push_back(Item(27, 1, 0, getSpriteFromSheet(16, 16), "Iron Hoe"));
            itemList.push_back(Item(28, 1, 0, getSpriteFromSheet(17, 16), "Diamond Hoe"));
            itemList.push_back(Item(29, 1, 0, getSpriteFromSheet(18, 16), "Gold Hoe"));

            itemList.push_back(Item(30, 64, 0, getSpriteFromSheet(3, 0), "Cobblestone"));
            itemList.push_back(Item(31, 64, 0, getSpriteFromSheet(12, 0), "Gold Ore"));
            itemList.push_back(Item(32, 64, 0, getSpriteFromSheet(13, 0), "Iron Ore"));
            itemList.push_back(Item(33, 64, 9, getSpriteFromSheet(8, 11), "Coal"));
            itemList.push_back(Item(34, 64, 0, getSpriteFromSheet(1, 12), "Iron Ingot"));
            itemList.push_back(Item(35, 64, 0, getSpriteFromSheet(17, 12), "Gold Ingot"));
            itemList.push_back(Item(36, 64, 0, getSpriteFromSheet(10, 13), "Diamond"));
            itemList.push_back(Item(37, 64, 0, getSpriteFromSheet(1, 19), "Nether Star"));
            itemList.push_back(Item(38, 64, 0, getSpriteFromSheet(10, 0), "Sand"));
            itemList.push_back(Item(39, 64, 0, getSpriteFromSheet(11, 0), "Gravel"));
            itemList.push_back(Item(40, 64, 0, getSpriteFromSheet(1, 1), "Glass"));
            itemList.push_back(Item(41, 64, 0, getSpriteFromSheet(12, 2), "Obsidian"));
            itemList.push_back(Item(42, 64, 0, getSpriteFromSheet(21, 4), "Beacon"));

            itemList.push_back(Item(43, 64, 0, getSpriteFromSheet(7, 16), "Raw Chicken"));
            itemList.push_back(Item(44, 64, 0, getSpriteFromSheet(8, 16), "Cooked Chicken"));
            itemList.push_back(Item(45, 64, 0, getSpriteFromSheet(14, 15), "Raw Beef"));
            itemList.push_back(Item(46, 64, 0, getSpriteFromSheet(15, 15), "Steak"));
            itemList.push_back(Item(47, 64, 0, getSpriteFromSheet(0, 15), "Rotten Flesh"));
            itemList.push_back(Item(48, 64, 4, getSpriteFromSheet(20, 17), "Blaze Powder"));
            itemList.push_back(Item(49, 16, 0, getSpriteFromSheet(16, 15), "Ender Pearls"));
            itemList.push_back(Item(50, 16, 0, getSpriteFromSheet(18, 17), "Eye of Ender"));

            itemList.push_back(Item(51, 64, 0, getSpriteFromSheet(3, 12), "Wheat"));
            itemList.push_back(Item(52, 64, 0, getSpriteFromSheet(19, 12), "Bread"));
            itemList.push_back(Item(53, 64, 0, getSpriteFromSheet(5, 16), "Potato"));
            itemList.push_back(Item(54, 64, 0, getSpriteFromSheet(4, 16), "Cooked potato"));
            itemList.push_back(Item(55, 64, 0, getSpriteFromSheet(11, 11), "Apple"));
            itemList.push_back(Item(56, 64, 0, getSpriteFromSheet(12, 11), "Golden Apple"));
        }
};