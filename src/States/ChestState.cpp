#include "ChestState.h"

ChestState::ChestState(Player* player) : State(player) {
    this->background.load("images/states/chest.png");
    // Create the chest inventory. (A list of 27 ItemContainers)
    const int VERTICAL_OFFSET = 72;
    const int HORIZONTAL_OFFSET = 32;
    const int DISTANCE_BETWEEN_CONTAINERS = 72;
    const int ROWS = 3;
    const int COLS = 9;
    for (int y = VERTICAL_OFFSET; y < VERTICAL_OFFSET + (DISTANCE_BETWEEN_CONTAINERS*ROWS); y = y + DISTANCE_BETWEEN_CONTAINERS) {
        for (int x = HORIZONTAL_OFFSET; x < HORIZONTAL_OFFSET + (DISTANCE_BETWEEN_CONTAINERS*COLS); x = x + DISTANCE_BETWEEN_CONTAINERS) {
            this->chestInventory.push_back(ItemContainer(x,y));
        }
    }
}

void ChestState::addItem(Item itm, int count) {
    int i = 0;
    // Scan for the first available slot.
    while (!this->chestInventory[i].isEmpty() && i <= 26) {i++;}
    if (i == 27) return; // The chest is full.
    this->chestInventory[i].setCurrentItem(itm);
    this->chestInventory[i].setItemCount(count);
}
void ChestState::addItem(Item itm, int count, int slot){
    // Out of range checker
    if (slot < 0 || slot > 26) { slot = 0; }
    this->chestInventory[slot].setCurrentItem(itm);
    this->chestInventory[slot].setItemCount(count);
};
void ChestState::draw(){
    background.draw(0,0);
    for (auto slot : this->chestInventory) {
        slot.draw();
    }
    this->getPlayer()->draw();
};
void ChestState::mouseMoved(int x, int y){
    State::mouseMoved(x,y);
    // Check if the mouse enters any of the state's containers
    for (auto& slot : this->chestInventory) { slot.mouseEntered(x,y); }
};
void ChestState::mousePressed(int x, int y, int button){
    State::mousePressed(x,y,button);
    if (button == 0) for (auto& slot : this->chestInventory) { slot.leftMouseClicked(x,y,getPlayer()->getCursorContainer()); }
    if (button == 2) for (auto& slot : this->chestInventory) { slot.rightMouseClicked(x,y,getPlayer()->getCursorContainer()); }
};

