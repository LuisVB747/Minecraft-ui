#include "BossState.h"

BossState::BossState(Player* player, ItemHandler* instantiator) : State(player){
    this->instantiator = instantiator;
    this->background.load("images/states/boss.png");
    this->SwordContainer = ItemContainer(176, 72);
    this->ShieldContainer = ItemContainer(176, 144);
    this->FoodContainer = ItemContainer(176,216);

    this->bossHealth = bossHealth;
    this->bossDamage = bossDamage;
    this->bossAccuracy = bossAccuracy;
};

void BossState::equipTools(Item newItem){
    string itemName = newItem.getName();

    if (itemName.find("Sword")!= std::string::npos) {
        this->SwordContainer.setCurrentItem(newItem);
    }
    else if(itemName.find("Shield")!= std::string::npos){
        this->ShieldContainer.setCurrentItem(newItem);
    }
    else if(itemName.find("Cooked")!= std::string::npos || 
            itemName.find("Steak")!= std::string::npos || 
            itemName.find("Bread")!= std::string::npos || 
            itemName.find("Potato")!= std::string::npos || 
            itemName.find("Apple")!= std::string::npos){
        this->FoodContainer.setCurrentItem(newItem);
    }
}

bool BossState::canEquip(){
    Item cursorItem = getPlayer()->getCursorContainer().getCurrentItem();
    if(cursorItem.getName().find("Sword") != std::string::npos ||
       cursorItem.getName().find("Shield") != std::string::npos ||
       cursorItem.getName().find("Cooked") != std::string::npos ||
       cursorItem.getName().find("Steak") != std::string::npos ||
       cursorItem.getName().find("Bread") != std::string::npos ||
       cursorItem.getName().find("Potato") != std::string::npos ||
       cursorItem.getName().find("Apple") != std::string::npos){
        return true;
    }
    else{
        return false;
    }
}


int BossState::getBossHealth(){return this->bossHealth;}

/**
 * @brief Gets the current boss attack damage.
 * @return The current boss attack damage.
 */
int BossState::getBossDamage(){return this->bossDamage;}

/**
 * @brief Gets the current boss attack accuracy.
 * @return The current boss accuracy.
 */
int BossState::getBossAccuracy(){return this->bossAccuracy;}



void BossState::update(){}


void BossState::draw(){
    background.draw(0,0);
    this->SwordContainer.draw();
    this->ShieldContainer.draw();
    this->FoodContainer.draw();
    this->getPlayer()->draw();
}


void BossState::mouseMoved(int x, int y){
    State::mouseMoved(x,y);
    this->SwordContainer.mouseEntered(x,y);
    this->ShieldContainer.mouseEntered(x,y);
    this->FoodContainer.mouseEntered(x,y);
}


void BossState::mousePressed(int x, int y, int button){
    State::mousePressed(x,y,button);

    ItemContainer& cursorContainer = getPlayer()->getCursorContainer();
    Item cursorItem = cursorContainer.getCurrentItem();

    if (button == 0 || button == 2) {
        if (SwordContainer.isMouseHovering()) {
            if (cursorContainer.isEmpty()) {
                // Unequip: Move the sword to the cursor container
                cursorContainer.setCurrentItem(SwordContainer.getCurrentItem());
                cursorContainer.setItemCount(1);
                SwordContainer.empty(); // Clear the helmet slot
            } else if (cursorItem.getName().find("Sword") != std::string::npos) {
                // Equip: Move the cursor item to the sword slot
                equipTools(cursorItem);
                cursorContainer.empty(); // Clear the cursor
            }
        } else if (ShieldContainer.isMouseHovering()) {
            if (cursorContainer.isEmpty()) {
                // Unequip: Move the shield to the cursor container
                cursorContainer.setCurrentItem(ShieldContainer.getCurrentItem());
                cursorContainer.setItemCount(1);
                ShieldContainer.empty(); // Clear the chestplate slot
            } else if (cursorItem.getName().find("Shield") != std::string::npos) {
                // Equip: Move the cursor item to the shield slot
                equipTools(cursorItem);
                cursorContainer.empty(); // Clear the cursor
            } 
        } else if (FoodContainer.isMouseHovering()) {
                if (cursorContainer.isEmpty()) {
                    // Unequip: Move the food to the cursor container
                    cursorContainer.setCurrentItem(FoodContainer.getCurrentItem());
                    cursorContainer.setItemCount(1);
                    FoodContainer.empty(); // Clear the food slot
                } else if (cursorItem.getName().find("Cooked") != std::string::npos ||
                           cursorItem.getName().find("Steak") != std::string::npos ||
                           cursorItem.getName().find("Bread") != std::string::npos ||
                           cursorItem.getName().find("Potato") != std::string::npos ||
                           cursorItem.getName().find("Apple") != std::string::npos){
                    // Equip: Move the cursor item to the food slot
                    equipTools(cursorItem);
                    cursorContainer.empty(); // Clear the cursor
                } 
        }
    }
}

void BossState::keyPressed(int key){}

