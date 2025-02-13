#include "FurnaceState.h"

FurnaceState::FurnaceState(Player* player, ItemHandler* instantiatr) : State(player) {
    this->fuel = 0;
    this->instantiator = instantiatr;
    this->background.load("images/states/furnace.png");
    this->fuelContainer = ItemContainer(224, 212); // These coordinate values were obtained via PaintMS.
    this->burningContainer = ItemContainer(224, 68);
    this->resultContainer = ItemContainer(464, 139);
    addSmeltableItems();
};
/**
 * @brief Checks if the furnace can smelt the current item.
 * 
 * This method checks several conditions to determine if the furnace can smelt the item in the burning container:
 * - The burning container must not be empty.
 * - The result container must not be full.
 * - There must be fuel available. Either in the furnace's fuel integer variable, or stored in the fuel container's item.
 * - If the result container is not empty, it must contain the same type of item as the resultant item from smelting.
 * 
 * @return true if the furnace can smelt the current item, false otherwise.
 */
bool FurnaceState::canSmelt() {
    // TODO: Implement this method.
    return true;
}

/**
 * Smelts the current item in the burning container.
 * 
 * This method performs the smelting process in the furnace. It checks if there is fuel available,
 * and if not, it refills the fuel from the fuel container. It then processes the item in the burning
 * container, moving the resultant item to the result container. If the result container is empty, 
 * it adds the new item; otherwise, it increments the item count. Finally, it decrements the item 
 * count in the burning container and empties it if the count reaches zero.
 */
void FurnaceState::smelt() {
    // Refuel if necessary
    if (fuel == 0) { 
        fuel = fuelContainer.getCurrentItem().getFuelLevel(); 
        fuelContainer.deductOne();
    }
    // If its empty, we set the resultant item to the smelted item.
    if (resultContainer.isEmpty()) { 
        Item newItem = instantiator->getItemFromNumber(getResultantItemNumber(burningContainer.getCurrentItem()));
        resultContainer.setCurrentItem(newItem);
        resultContainer.setItemCount(1);
    }else {
        resultContainer.addOne();
    }

    burningContainer.deductOne();
    // If the burningContainer is empty we reset the fuel back to zero.
    burningContainer.isEmpty() ? fuel = 0 : fuel--;
    
}


void FurnaceState::update() { if (canSmelt()) smelt(); };

void FurnaceState::draw() {
    background.draw(0,0);
    this->fuelContainer.draw();
    this->burningContainer.draw();
    this->resultContainer.draw();
    this->getPlayer()->draw();
}

void FurnaceState::mouseMoved(int x, int y) {
    State::mouseMoved(x,y);
    // Check if the mouse enters any of the state's containers
    this->fuelContainer.mouseEntered(x,y);
    this->burningContainer.mouseEntered(x,y);
    this->resultContainer.mouseEntered(x,y);
};

void FurnaceState::mousePressed(int x, int y, int button) {
    State::mousePressed(x,y,button);
    if (button == 0) {
        // Only allow interaction if the player's container is empty
        if (this->getPlayer()->getCursorContainer().isEmpty()) this->resultContainer.leftMouseClicked(x,y,this->getPlayer()->getCursorContainer());
        // Only allow interaction if the player's container is empty (extracting) or if the player's item is fuel
        if (this->getPlayer()->getCursorContainer().isEmpty() || this->getPlayer()->getCursorContainer().getCurrentItem().getFuelLevel() > 0) this->fuelContainer.leftMouseClicked(x,y,this->getPlayer()->getCursorContainer());
        //  Only allow interaction if the player's container is empty (extracting) or if the player's item is smeltable
        if (this->getPlayer()->getCursorContainer().isEmpty() || isItemSmeltable(this->getPlayer()->getCursorContainer().getCurrentItem())) this->burningContainer.leftMouseClicked(x,y,this->getPlayer()->getCursorContainer());
    }
    if (button == 2) {
        // Only allow interaction with the the player's container is empty
        if (this->getPlayer()->getCursorContainer().isEmpty()) this->resultContainer.rightMouseClicked(x,y,this->getPlayer()->getCursorContainer()); 
        // Only allow interaction if the player's container is empty (taking half) or if the player's container is fuel (placing one)
        if (this->getPlayer()->getCursorContainer().isEmpty() || this->getPlayer()->getCursorContainer().getCurrentItem().getFuelLevel() > 0) this->fuelContainer.rightMouseClicked(x,y,this->getPlayer()->getCursorContainer());
        // Only allow interaction if the player's container is empty (taking half) or if the player's item is smeltable
        if (this->getPlayer()->getCursorContainer().isEmpty() || isItemSmeltable(this->getPlayer()->getCursorContainer().getCurrentItem())) this->burningContainer.rightMouseClicked(x,y,this->getPlayer()->getCursorContainer());
    }
};

void FurnaceState::addSmeltableItems() {
    this->smeltableItems = {2};
}

int FurnaceState::getResultantItemNumber(Item itm) {
    int itemNumber = itm.getItemNumber();
    /*
        switch is just a fancier if statement.
        case (smeltable item number):
            return (resulting item number);

        See ItemHandler.h for item ids.
        Defaults to 0 (air) if no case was met.
    */
    switch (itemNumber) {
        case 2:
            return 33;
        case 31:
            return 35;
        case 32:
            return 34;
        case 38:
            return 40;
        case 43:
            return 44;
        case 45:
            return 46;
        case 53:
            return 54;
        default:
            return 0;
    }
}
