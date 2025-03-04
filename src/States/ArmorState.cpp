#include "ArmorState.h"

ArmorState :: ArmorState(Player* player, ItemHandler* instantiatr) : State(player){
    this->background.load("images/states/Armor.png");
    const int VERTICAL_OFFSET = 44;
    const int HORIZONTAL_OFFSET = 322;
    const int DISTANCE_BETWEEN_CONTAINERS = 70;
    const int ROWS = 5;
    const int COLS = 1;
    for (int y = VERTICAL_OFFSET; y < VERTICAL_OFFSET + (DISTANCE_BETWEEN_CONTAINERS*ROWS); y = y + DISTANCE_BETWEEN_CONTAINERS) {
        for (int x = HORIZONTAL_OFFSET; x < HORIZONTAL_OFFSET + (DISTANCE_BETWEEN_CONTAINERS*COLS); x = x + DISTANCE_BETWEEN_CONTAINERS) {
            // Create an empty container at x, y
            this->armorGrid.push_back(ItemContainer(x,y));
        }
    }
};
