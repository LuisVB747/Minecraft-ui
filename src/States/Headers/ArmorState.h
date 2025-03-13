#pragma once
#include "State.h"

/**
 * @class ArmorState
 * @brief Represents the state in which the player manages and equips armor.
 */
class ArmorState : public State {
private: 
    vector<ItemContainer> armorGrid; //grid for the armor
    ItemHandler* instantiator; // pointer to the item
    ItemContainer Helmet;
    ItemContainer Chestplate;
    ItemContainer Leggins;
    ItemContainer Boots;
    int defense;

public:
    /**
     * @brief Constructs an ArmorState object with a player pointer.
     * @param player Pointer to the player object.
     * @param instantiator Item handler pointer
     */
    ArmorState(Player* player, ItemHandler* instantiator);

    /**
     * @brief Equips armor if the player has it in their inventory.
     * @param slot The name of the slot.
     */
    void equipArmor(Item newItem);

    /**
     * @brief Removes equipped armor.
     * @param slot The slot from which to remove the armor.
     */
    bool canEquip();

    /**
     * @brief Updates the state.
     */
    void update();

    /**
     * @brief Draws the state.
     */
    void draw();

    void keyPressed(int key);
    /**
     * @brief Handles mouse press events.
     * @param x The x-coordinate of the mouse.
     * @param y The y-coordinate of the mouse.
     */
    void mouseMoved(int x, int y);

    /**
     * @brief Handles key press events. Mandatory unused implementation.
     */
    void mousePressed(int x, int y, int button);

    int calculateArmorDefense(const std::string& armorName);
    void removeOldDefense(ItemContainer &armorSlot);

};

