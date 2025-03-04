#pragma once
#include "State.h"
#include "Player.h"

/**
 * @class ArmorState
 * @brief Represents the state in which the player manages and equips armor.
 */
class ArmorState : public State {
private: 

    vector<ItemContainer> armorGrid; //grid for the armor
    ItemHandler* instantiator; // pointer to the item
public:
    /**
     * @brief Constructs an ArmorState object with a player pointer.
     * @param plyr Pointer to the player object.
     */
    ArmorState(Player* player, ItemHandler* instantiator);

    /**
     * @brief Equips armor if the player has it in their inventory.
     * @param itemID The ID of the armor item.
     */
    void equipArmor(int itemID);

    /**
     * @brief Removes equipped armor.
     * @param slot The slot from which to remove the armor.
     */
    void removeArmor(int slot);

    /**
     * @brief Updates the state.
     */
    void update() override;

    /**
     * @brief Draws the state.
     */
    void draw() override;

    /**
     * @brief Handles key press events.
     * @param key The key that was pressed.
     */
    void keyPressed(int key) override;
};
