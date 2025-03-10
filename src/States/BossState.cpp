#include "BossState.h"
#include <random>

BossState::BossState(Player* player, ItemHandler* instantiator) : State(player){
    this->instantiator = instantiator;
    this->background.load("images/states/boss.png");
    this->SwordContainer = ItemContainer(176, 72);
    this->ShieldContainer = ItemContainer(176, 144);
    this->FoodContainer = ItemContainer(176,216);


    // Boss Stats 
    this->bossHealth = 100;
    this->bossDamage = 15;
    this->bossAccuracy = 7;
    // Player Stats
    this->playerDamage = 0;
    this->playerHealth = 100;
    // multipliers
    this->swordDamage = 0;  // (After revising this variable could have been just the player Damage -_-)
    this->foodHealing = 0;


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

void BossState::calculateSwordDamage(const std::string& swordName) {
    if (swordName.find("Ender Sword") != std::string::npos) {
        swordDamage = 20; // Ender Sword deals 20 damage
    } else if (swordName.find("Diamond Sword") != std::string::npos) {
        swordDamage = 20; // Diamond Sword deals 15 damage
    } else if (swordName.find("Iron Sword") != std::string::npos) {
        swordDamage = 15; // Iron Sword deals 12 damage
    } else if (swordName.find("Stone Sword") != std::string::npos) {
        swordDamage = 10; // Stone Sword deals 10 damage
    } else if (swordName.find("Wooden Sword") != std::string::npos) {
        swordDamage = 5; // Wooden Sword deals 5 damage
    }
    swordDamage = 0; // Default damage if no sword is equipped or the sword is unknown
}


void BossState::calculateHealing(const std::string& foodName){
    if (foodName.find("Golden Apple") != std::string::npos) {
        foodHealing = 30; // Golden Apple heals 20 health
    } else if (foodName.find("Steak") != std::string::npos) {
        foodHealing = 15; // Steak heals 15 health
    } else if (foodName.find("Cooked") != std::string::npos) {
        foodHealing = 15; // Chicken heals 15 health
    } else if (foodName.find("Bread") != std::string::npos) {
        foodHealing = 5; // Bread heals 5 health
    } else if (foodName.find("Potato") != std::string::npos) {
        foodHealing = 5; // Potato heals 5 health
    } else if (foodName.find("Apple") != std::string::npos) {
        foodHealing =  5; // Apple heals 5 health
    }
    foodHealing =  0; // Default healing if no food is equipped
}


void BossState::doHealing(int foodHealing){
    this->playerHealth += foodHealing;
    if (this->playerHealth > 100) {
        this->playerHealth = 100;
    }

}

void BossState::damagePlayer(int bossDamage, int bossAccuracy){

    // Generate random number between 1 and 10
    static std::random_device rd;  
    static std::mt19937 gen(rd());  
    static std::uniform_int_distribution<> dis(1, 10);

    int randomNumber = dis(gen);

    if (randomNumber <= bossAccuracy) {
        if (this->ShieldContainer.getCurrentItem().getName().find("Shield") != std::string::npos) {
            // Shield equipped: Reduce damage by 30%
            bossDamage /= 3;
        }
        this->playerHealth -= bossDamage;
    
        if (this->playerHealth <= 0) {
            // Player has died
            this->playerHealth = 0;
        }
    } else {
        // Boss missed
    }
}

void BossState::damageBoss(int playerDamage){
    if (this->SwordContainer.getCurrentItem().getName().find("Sword") != std::string::npos) {
        // If sword is equipped, add the sword damage to the player damage
        playerDamage += swordDamage;
    }
    this->bossHealth -= playerDamage;

    if (this->bossHealth <= 0) {
        // Boss has died
        this->bossHealth = 0;
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



void BossState::update(){


    // Item currentSword = SwordContainer.getCurrentItem();
    // int playerDamage = calculateSwordDamage(currentSword.getName());

}


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

