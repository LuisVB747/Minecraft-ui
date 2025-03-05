#include "ArmorState.h"

ArmorState :: ArmorState(Player* player, ItemHandler* instantiator) : State(player){
    this->instantiator = instantiator; 
    this->background.load("images/states/armor.png");
    this->Helmet = ItemContainer(323,50);
    this->Chestplate = ItemContainer(323, 120);
    this->Leggins = ItemContainer(323, 190);
    this-> Boots = ItemContainer(323, 260);
    
};

void ArmorState::equipArmor(Item newItem) {
    string itemName = newItem.getName(); 

    if (itemName.find("helmet") != std::string::npos) {
        this->Helmet.setCurrentItem(newItem);
    } 
    else if (itemName.find("chestplate") != std::string::npos) {
        this->Chestplate.setCurrentItem(newItem);
    } 
    else if (itemName.find("leggings") != std::string::npos) {
        this->Leggins.setCurrentItem(newItem);
    } 
    else if (itemName.find("boots") != std::string::npos) {
        this->Boots.setCurrentItem(newItem);
    } 
}

bool ArmorState::canEquip() {
    Item cursorItem = getPlayer()->getCursorContainer().getCurrentItem();
    if(cursorItem.getName().find("helmet") != std::string::npos || 
    cursorItem.getName().find("chestplate") != std::string::npos || 
    cursorItem.getName().find("leggings") != std::string::npos || 
    cursorItem.getName().find("boots") != std::string::npos){
        return true;
    }
    else{
        return false;
    }
 }

void ArmorState::update() { 
    // if(canEquip()) { 
    // Item cursorItem = getPlayer()->getCursorContainer().getCurrentItem();
    //     equipArmor(cursorItem);
//  }

}

void ArmorState::draw() {
    background.draw(0,0);
    this->Helmet.draw();
    this->Chestplate.draw();
    this->Leggins.draw();
    this->Boots.draw();
    this->getPlayer()->draw();
    // for (auto& slot : getPlayer()->getInventory()) {
    //     slot.draw();
    // }
}
void ArmorState::mouseMoved(int x, int y){
    State::mouseMoved(x,y);

    this->Helmet.mouseEntered(x,y);
    this->Chestplate.mouseEntered(x,y);
    this->Leggins.mouseEntered(x,y);
    this->Boots.mouseEntered(x,y);
    // for (auto& slot : getPlayer()->getInventory()) {
    //     slot.mouseEntered(x, y);
    // }
}

void ArmorState::keyPressed(int key){

}

void ArmorState::mousePressed(int x, int y, int button) {
    State::mousePressed(x,y,button);

    ItemContainer& cursorContainer = getPlayer()->getCursorContainer();
    Item cursorItem = cursorContainer.getCurrentItem();

    // Handle left mouse click
    if (button == 0 || button == 2) {
        if (Helmet.isMouseHovering()) {
            if (cursorContainer.isEmpty()) {
                // Unequip: Move the helmet to the cursor container
                cursorContainer.setCurrentItem(Helmet.getCurrentItem());
                cursorContainer.setItemCount(1);
                Helmet.empty(); // Clear the helmet slot
            } else if (cursorItem.getName().find("helmet") != std::string::npos) {
                // Equip: Move the cursor item to the helmet slot
                equipArmor(cursorItem);
                cursorContainer.empty(); // Clear the cursor
            }
        } else if (Chestplate.isMouseHovering()) {
            if (cursorContainer.isEmpty()) {
                // Unequip: Move the chestplate to the cursor container
                cursorContainer.setCurrentItem(Chestplate.getCurrentItem());
                cursorContainer.setItemCount(1);
                Chestplate.empty(); // Clear the chestplate slot
            } else if (cursorItem.getName().find("chestplate") != std::string::npos) {
                // Equip: Move the cursor item to the chestplate slot
                equipArmor(cursorItem);
                cursorContainer.empty(); // Clear the cursor
            }
        } else if (Leggins.isMouseHovering()) {
            if (cursorContainer.isEmpty()) {
                // Unequip: Move the leggings to the cursor container
                cursorContainer.setCurrentItem(Leggins.getCurrentItem());
                cursorContainer.setItemCount(1);
                Leggins.empty(); // Clear the leggings slot
            } else if (cursorItem.getName().find("leggings") != std::string::npos) {
                // Equip: Move the cursor item to the leggings slot
                equipArmor(cursorItem);
                cursorContainer.empty(); // Clear the cursor
            }
        } else if (Boots.isMouseHovering()) {
            if (cursorContainer.isEmpty()) {
                // Unequip: Move the boots to the cursor container
                cursorContainer.setCurrentItem(Boots.getCurrentItem());
                cursorContainer.setItemCount(1);
                Boots.empty(); // Clear the boots slot
            } else if (cursorItem.getName().find("boots") != std::string::npos) {
                // Equip: Move the cursor item to the boots slot
                equipArmor(cursorItem);
                cursorContainer.empty(); // Clear the cursor
            }
        }
    }
}

    // Handle left mouse click
    // if (button == 0) {
    //     if (Helmet.isMouseHovering()) {
    //         Helmet.leftMouseClicked(x, y, getPlayer()->getCursorContainer());
    //     } else if (Chestplate.isMouseHovering()) {
    //         Chestplate.leftMouseClicked(x, y, getPlayer()->getCursorContainer());
    //     } else if (Leggins.isMouseHovering()) {
    //         Leggins.leftMouseClicked(x, y, getPlayer()->getCursorContainer());
    //     } else if (Boots.isMouseHovering()) {
    //         Boots.leftMouseClicked(x, y, getPlayer()->getCursorContainer());
    //     }
    // }
    // // Handle right mouse click
    // else if (button == 2) {
    //     if (Helmet.isMouseHovering()) {
    //         Helmet.rightMouseClicked(x, y, getPlayer()->getCursorContainer());
    //     } else if (Chestplate.isMouseHovering()) {
    //         Chestplate.rightMouseClicked(x, y, getPlayer()->getCursorContainer());
    //     } else if (Leggins.isMouseHovering()) {
    //         Leggins.rightMouseClicked(x, y, getPlayer()->getCursorContainer());
    //     } else if (Boots.isMouseHovering()) {
    //         Boots.rightMouseClicked(x, y, getPlayer()->getCursorContainer());
    //     }
    // }
