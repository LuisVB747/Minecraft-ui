#include "BossState.h"
#include "ArmorState.h"
#include <random>
#include <iostream>

const int PLAYER_ATTACK_DURATION = 60;    // Ticks for player attack resolution
const int BOSS_ATTACK_DURATION = 200;        // Ticks for boss attack resolution
const int TURN_TRANSITION_DURATION = 100;    // Ticks for transition between turns

BossState::BossState(Player* player, ItemHandler* instantiator, ArmorState* armorState) : State(player) {
    this->instantiator = instantiator;
    this->armorState = armorState;

    // Images 
    this->background.load("images/states/boss.png");
    this->halfHeart.load("images/sprites/half_heart.png");
    this->halfHeartBoss.load("images/sprites/half_heart_boss.png");
    this->emptyHeart.load("images/sprites/empty_heart.png");

    // Containers
    this->bossImage.load("images/sprites/ender.png");
    this->bossDamageImage.load("images/sprites/ender_damaged.png");
    this->bossAttackImage.load("images/sprites/ender_attack.png");
    this->SwordContainer = ItemContainer(176, 72);
    this->ShieldContainer = ItemContainer(176, 144); 
    this->FoodContainer = ItemContainer(176,216);

    // Boss Stats 
    this->bossHealth = 500; // max 500
    this->bossDamage = 15;
    
    this->bossAccuracy = 8;
    // Player Stats
    this->playerDamage = 0;
    this->playerHealth = 100;
    // Multipliers
    this->swordDamage = 0;  // (After revising this variable could have been just the player Damage)
    this->foodHealing = 0;

    // Initialize tick system variables:
    tickCounter = 0;
    currentTurn = WAITING_FOR_INPUT;
    lastTurn = WAITING_FOR_INPUT;
    this-> isDamaged = false;     // Tracks if the boss is in a damaged state
    this-> isAttack = false; // tracks the boss attacks
    this-> damageStartTime = 0;  // Timer for showing the damage effect (in seconds)
    this-> damageDuration = 0.75f;  // Duration to show the damage image

}

void BossState::equipTools(Item newItem) {
    std::string itemName = newItem.getName();

    if (itemName.find("Sword") != std::string::npos) {
        this->SwordContainer.setCurrentItem(newItem);
        calculateSwordDamage(itemName);
        playerDamage = swordDamage;
        std::cout << "[DEBUG] Equipped Sword. PlayerDamage: " << playerDamage << std::endl;
    }
    else if(itemName.find("Shield") != std::string::npos) {
        this->ShieldContainer.setCurrentItem(newItem);
        std::cout << "[DEBUG] Equipped Shield." << std::endl;
    }
    else if(itemName.find("Cooked") != std::string::npos || 
            itemName.find("Steak") != std::string::npos || 
            itemName.find("Bread") != std::string::npos || 
            itemName.find("Potato") != std::string::npos || 
            itemName.find("Apple") != std::string::npos) {
        this->FoodContainer.setCurrentItem(newItem);
        std::cout << "[DEBUG] Equipped Food." << std::endl;
    }
}

bool BossState::canEquip() {
    Item cursorItem = getPlayer()->getCursorContainer().getCurrentItem();
    if(cursorItem.getName().find("Sword") != std::string::npos ||
       cursorItem.getName().find("Shield") != std::string::npos ||
       cursorItem.getName().find("Cooked") != std::string::npos ||
       cursorItem.getName().find("Steak") != std::string::npos ||
       cursorItem.getName().find("Bread") != std::string::npos ||
       cursorItem.getName().find("Potato") != std::string::npos ||
       cursorItem.getName().find("Apple") != std::string::npos) {
        return true;
    }
    else {
        return false;
    }
}

void BossState::calculateSwordDamage(const std::string& swordName) {
    if (swordName.find("Ender Sword") != std::string::npos) {
        swordDamage = 20; // Ender Sword deals 20 damage
    } else if (swordName.find("Diamond Sword") != std::string::npos) {
        swordDamage = 20; // Diamond Sword deals 20 damage
    } else if (swordName.find("Iron Sword") != std::string::npos) {
        swordDamage = 15; // Iron Sword deals 15 damage
    } else if (swordName.find("Stone Sword") != std::string::npos) {
        swordDamage = 10; // Stone Sword deals 10 damage
    } else if (swordName.find("Wooden Sword") != std::string::npos) {
        swordDamage = 5;  // Wooden Sword deals 5 damage
    } else {
        swordDamage = 0;
    }
}

void BossState::calculateHealing(const std::string& foodName) {
    if (foodName.find("Golden Apple") != std::string::npos) {
        foodHealing = 30; // Golden Apple heals 30 health
    } else if (foodName.find("Steak") != std::string::npos) {
        foodHealing = 15; // Steak heals 15 health
    } else if (foodName.find("Cooked") != std::string::npos) {
        foodHealing = 15; // Cooked food heals 15 health
    } else if (foodName.find("Bread") != std::string::npos) {
        foodHealing = 5;  // Bread heals 5 health
    } else if (foodName.find("Potato") != std::string::npos) {
        foodHealing = 5;  // Potato heals 5 health
    } else if (foodName.find("Apple") != std::string::npos) {
        foodHealing = 5;  // Apple heals 5 health
    } else {
        foodHealing = 0;  // Default healing if no recognized food is equipped
    }
}

void BossState::doHealing(int foodHealing) {
    this->playerHealth += foodHealing;
    if (this->playerHealth > 100) {
        this->playerHealth = 100;
    }
    std::cout << "[DEBUG] Healing performed. Player Health: " << playerHealth << std::endl;
}

void BossState::damagePlayer(int bossAccuracy) {
    static std::random_device rd;  
    static std::mt19937 gen(rd());  
    static std::uniform_int_distribution<> dis(1, 10);

    int randomNumber = dis(gen);
    if (randomNumber <= bossAccuracy) {
        if (this->ShieldContainer.getCurrentItem().getName().find("Shield") != std::string::npos) {
            bossDamage /= 3;  // Reduce damage if shield is equipped
        }
        this->playerHealth -= bossDamage;
        std::cout << "[DEBUG] Boss attacks! Player takes " << bossDamage << " damage. Player Health: " << playerHealth << std::endl;
        if (this->playerHealth <= 0) {
            this->playerHealth = 0;
        }
    } else {
        std::cout << "[DEBUG] Boss attack missed!" << std::endl;
    }
    isAttack = true;
    damageStartTime = ofGetElapsedTimef();
}

void BossState::damageBoss(int playerDamage) {
    // Use combined damage: playerDamage + swordDamage
    int totalDamage = playerDamage; // Here, we assume playerDamage is set to include the sword's bonus.
    this->bossHealth -= totalDamage;
    std::cout << "[DEBUG] Player attacks! Boss takes " << totalDamage << " damage. Boss Health: " << bossHealth << std::endl;
    if (this->bossHealth <= 0) {
        this->bossHealth = 0;
    }
    isDamaged = true;
    damageStartTime = ofGetElapsedTimef(); 
}

int BossState::getBossHealth() { return this->bossHealth; }
int BossState::getBossDamage() { return this->bossDamage; }
int BossState::getBossAccuracy() { return this->bossAccuracy; }

void BossState::update() {
    // Tick-based system implementation with debug statements
    if (bossHealth <= 0 || playerHealth <= 0) {
        currentTurn = GAME_OVER;
    }

    tickCounter++;

    switch(currentTurn) {
        case WAITING_FOR_INPUT:
            // std::cout << "[DEBUG] State: WAITING_FOR_INPUT, Tick: " << tickCounter << std::endl;
            // Wait here until a key press changes the state.
            break;

        case PLAYER_ATTACKING:
            std::cout << "[DEBUG] State: PLAYER_ATTACKING, Tick: " << tickCounter << std::endl;
            if (tickCounter >= PLAYER_ATTACK_DURATION) {
                // Resolve player's attack
                damageBoss(playerDamage + swordDamage);
                lastTurn = PLAYER_ATTACKING;
                tickCounter = 0;
                currentTurn = TURN_TRANSITION;
                std::cout << "[DEBUG] Transitioning from PLAYER_ATTACKING to TURN_TRANSITION." << std::endl;
            }
            break;

        case BOSS_ATTACKING:
            std::cout << "[DEBUG] State: BOSS_ATTACKING, Tick: " << tickCounter << std::endl;
            if (tickCounter >= BOSS_ATTACK_DURATION) {
                // Resolve boss's attack
                damagePlayer(bossAccuracy);
                lastTurn = BOSS_ATTACKING;
                tickCounter = 0;
                currentTurn = TURN_TRANSITION;
                std::cout << "[DEBUG] Transitioning from BOSS_ATTACKING to TURN_TRANSITION." << std::endl;
            }
            break;

        case TURN_TRANSITION:
            std::cout << "[DEBUG] State: TURN_TRANSITION, Tick: " << tickCounter << std::endl;
            if (tickCounter >= TURN_TRANSITION_DURATION) {
                tickCounter = 0;
                // Alternate turn: if the player attacked last, now it's the boss's turn; otherwise, return to waiting.
                if (lastTurn == PLAYER_ATTACKING) {
                    currentTurn = BOSS_ATTACKING;
                    std::cout << "[DEBUG] Turn transitioned: Now BOSS_ATTACKING." << std::endl;
                } else if (lastTurn == BOSS_ATTACKING) {
                    currentTurn = WAITING_FOR_INPUT;
                    std::cout << "[DEBUG] Turn transitioned: Now WAITING_FOR_INPUT." << std::endl;
                } else {
                    currentTurn = WAITING_FOR_INPUT;
                }
            }
            break;

        case GAME_OVER:
            std::cout << "[DEBUG] Game Over state reached." << std::endl;
            break;
    }
    if (isDamaged) {
        float elapsedTime = ofGetElapsedTimef() - damageStartTime;
        if (elapsedTime >= damageDuration) {
            isDamaged = false;  // Revert to normal boss image
        }
    }
    if (isAttack) {
        float elapsedTime = ofGetElapsedTimef() - damageStartTime;
        if (elapsedTime >= damageDuration) {
            isAttack = false;  // Revert to normal boss image
        }
    }
    this->bossDamage = 15 * (1.0f - (this->armorState->getDefense() * 1.0f / 200));
}

void BossState::draw() {
    background.draw(0,0);
    this->SwordContainer.draw();
    this->ShieldContainer.draw();
    this->FoodContainer.draw();
    this->getPlayer()->draw();


    // Draw Players Health
    if (this->playerHealth <= 90 && this->playerHealth > 80) {
        halfHeart.draw(172, 22);
    }else if (this->playerHealth <= 80 && this->playerHealth > 70) {
        emptyHeart.draw(172, 22);
    }else if (this->playerHealth <= 70 && this->playerHealth > 60) {
        emptyHeart.draw(172, 22);
        halfHeart.draw(134, 22);
    }else if (this->playerHealth <= 60 && this->playerHealth > 50) {
        emptyHeart.draw(172, 22);
        emptyHeart.draw(134, 22);
    }else if (this->playerHealth <= 50 && this->playerHealth > 40) {
        emptyHeart.draw(172, 22);
        emptyHeart.draw(134, 22);
        halfHeart.draw(96, 22);
    }else if (this->playerHealth <= 40 && this->playerHealth > 30) {
        emptyHeart.draw(172, 22);
        emptyHeart.draw(134, 22);
        emptyHeart.draw(96, 22);
    }else if (this->playerHealth <= 30 && this->playerHealth > 20) {
        emptyHeart.draw(172, 22);
        emptyHeart.draw(134, 22);
        emptyHeart.draw(96, 22);
        halfHeart.draw(58, 22);
    }else if (this->playerHealth <= 20 && this->playerHealth > 10) {
        emptyHeart.draw(172, 22);
        emptyHeart.draw(134, 22);
        emptyHeart.draw(96, 22);
        emptyHeart.draw(58, 22);
    }else if (this->playerHealth <= 10 && this->playerHealth > 0) {
        emptyHeart.draw(172, 22);
        emptyHeart.draw(134, 22);
        emptyHeart.draw(96, 22);
        emptyHeart.draw(58, 22);
        halfHeart.draw(20, 22);
    }else if (this->playerHealth == 0) {
        emptyHeart.draw(172, 22);
        emptyHeart.draw(134, 22);
        emptyHeart.draw(96, 22);
        emptyHeart.draw(58, 22);
        emptyHeart.draw(20, 22);
    }

    // Draw Boss Health
    if (this->bossHealth <= 475 && this->bossHealth > 450) {
        halfHeartBoss.draw(297, 287);
    }else if (this->bossHealth <= 450 && this->bossHealth > 425) {
        emptyHeart.draw(297, 287);
    }else if (this->bossHealth <= 425 && this->bossHealth > 400) {
        emptyHeart.draw(297, 287);
        halfHeartBoss.draw(336, 287);
    }else if (this->bossHealth <= 400 && this->bossHealth > 375) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(336, 287);
    }else if (this->bossHealth <= 375 && this->bossHealth > 350) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(336, 287);
        halfHeartBoss.draw(375, 287);
    }else if (this->bossHealth <= 350 && this->bossHealth > 325) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(336, 287);
        emptyHeart.draw(375, 287);
    }else if (this->bossHealth <= 325 && this->bossHealth > 300) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(336, 287);
        emptyHeart.draw(375, 287);
        halfHeartBoss.draw(411, 287);
    }else if (this->bossHealth <= 300 && this->bossHealth > 275) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(336, 287);
        emptyHeart.draw(375, 287);
        emptyHeart.draw(411, 287);
    }else if (this->bossHealth <= 275 && this->bossHealth > 250) { 
        emptyHeart.draw(297, 287);
        emptyHeart.draw(336, 287);
        emptyHeart.draw(375, 287);
        emptyHeart.draw(411, 287);
        halfHeartBoss.draw(449, 287);
    }else if (this->bossHealth <= 250 && this->bossHealth > 225) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(336, 287);
        emptyHeart.draw(375, 287);
        emptyHeart.draw(411, 287);
        emptyHeart.draw(449, 287);
    }else if (this->bossHealth <= 225 && this->bossHealth > 200) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(335, 287);
        emptyHeart.draw(373, 287);
        emptyHeart.draw(411, 287);
        emptyHeart.draw(449, 287);
        halfHeartBoss.draw(487, 287);
    }else if (this->bossHealth <= 200 && this->bossHealth > 175) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(335, 287);
        emptyHeart.draw(373, 287);
        emptyHeart.draw(411, 287);
        emptyHeart.draw(449, 287);
        emptyHeart.draw(487, 287);
    }else if (this->bossHealth <= 175 && this->bossHealth > 150) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(335, 287);
        emptyHeart.draw(373, 287);
        emptyHeart.draw(411, 287);
        emptyHeart.draw(449, 287);
        emptyHeart.draw(487, 287);
        halfHeartBoss.draw(525, 287);
    }else if (this->bossHealth <= 150 && this->bossHealth > 125) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(335, 287);
        emptyHeart.draw(373, 287);
        emptyHeart.draw(411, 287);
        emptyHeart.draw(449, 287);
        emptyHeart.draw(487, 287);
        emptyHeart.draw(525, 287);
    }else if (this->bossHealth <= 125 && this->bossHealth > 100) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(335, 287);
        emptyHeart.draw(373, 287);
        emptyHeart.draw(411, 287);
        emptyHeart.draw(449, 287);
        emptyHeart.draw(487, 287);
        emptyHeart.draw(525, 287);
        halfHeartBoss.draw(563, 287);
    }else if (this->bossHealth <= 100 && this->bossHealth > 75) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(335, 287);
        emptyHeart.draw(373, 287);
        emptyHeart.draw(411, 287);
        emptyHeart.draw(449, 287);
        emptyHeart.draw(487, 287);
        emptyHeart.draw(525, 287);
        emptyHeart.draw(563, 287);
    }else if (this->bossHealth <= 75 && this->bossHealth > 50) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(335, 287);
        emptyHeart.draw(373, 287);
        emptyHeart.draw(411, 287);
        emptyHeart.draw(449, 287);
        emptyHeart.draw(487, 287);
        emptyHeart.draw(525, 287);
        emptyHeart.draw(563, 287);
        halfHeartBoss.draw(601, 287);
    }else if (this->bossHealth <= 50 && this->bossHealth > 25) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(335, 287);
        emptyHeart.draw(373, 287);
        emptyHeart.draw(411, 287);
        emptyHeart.draw(449, 287);
        emptyHeart.draw(487, 287);
        emptyHeart.draw(525, 287);
        emptyHeart.draw(563, 287);
        emptyHeart.draw(601, 287);
    }else if (this->bossHealth <= 25 && this->bossHealth > 0) {
        emptyHeart.draw(297, 287);
        emptyHeart.draw(335, 287);
        emptyHeart.draw(373, 287);
        emptyHeart.draw(411, 287);
        emptyHeart.draw(449, 287);
        emptyHeart.draw(487, 287);
        emptyHeart.draw(525, 287);
        emptyHeart.draw(563, 287);
        emptyHeart.draw(601, 287);
        halfHeartBoss.draw(639, 287);
    }else if (this->bossHealth == 0) {
        emptyHeart.draw(297, 287); 
        emptyHeart.draw(335, 287);
        emptyHeart.draw(373, 287);
        emptyHeart.draw(411, 287);
        emptyHeart.draw(449, 287);
        emptyHeart.draw(487, 287);
        emptyHeart.draw(525, 287);
        emptyHeart.draw(563, 287);
        emptyHeart.draw(601, 287);
        emptyHeart.draw(639, 287);
    }
    if (isDamaged) {
        bossDamageImage.draw(265, 13);  // Adjust (x, y) position as needed
    } 
    else if (isAttack){
        bossAttackImage.draw(265,13);
    }
    else {
        bossImage.draw(265, 13);
    }
}
    

void BossState::mouseMoved(int x, int y) {
    State::mouseMoved(x,y);
    this->SwordContainer.mouseEntered(x,y);
    this->ShieldContainer.mouseEntered(x,y);
    this->FoodContainer.mouseEntered(x,y);
}

void BossState::mousePressed(int x, int y, int button) {
    State::mousePressed(x,y,button);

    ItemContainer& cursorContainer = getPlayer()->getCursorContainer();
    Item cursorItem = cursorContainer.getCurrentItem();

    if (button == 0 || button == 2) {
        if (SwordContainer.isMouseHovering()) {
            if (cursorContainer.isEmpty()) {
                cursorContainer.setCurrentItem(SwordContainer.getCurrentItem());
                cursorContainer.setItemCount(1);
                SwordContainer.empty();
            } else if (cursorItem.getName().find("Sword") != std::string::npos) {
                equipTools(cursorItem);
                cursorContainer.empty();
            }
        } else if (ShieldContainer.isMouseHovering()) {
            if (cursorContainer.isEmpty()) {
                cursorContainer.setCurrentItem(ShieldContainer.getCurrentItem());
                cursorContainer.setItemCount(1);
                ShieldContainer.empty();
            } else if (cursorItem.getName().find("Shield") != std::string::npos) {
                equipTools(cursorItem);
                cursorContainer.empty();
            }
        } else if (FoodContainer.isMouseHovering()) {
            if (cursorContainer.isEmpty()) {
                cursorContainer.setCurrentItem(FoodContainer.getCurrentItem());
                cursorContainer.setItemCount(1);
                FoodContainer.empty();
            } else if (cursorItem.getName().find("Cooked") != std::string::npos ||
                       cursorItem.getName().find("Steak") != std::string::npos ||
                       cursorItem.getName().find("Bread") != std::string::npos ||
                       cursorItem.getName().find("Potato") != std::string::npos ||
                       cursorItem.getName().find("Apple") != std::string::npos) {
                equipTools(cursorItem);
                cursorContainer.empty();
            }
        }
    }
}

void BossState::keyPressed(int key) {
    // Print out the received key code for debugging
    std::cout << "[DEBUG] keyPressed received key: " << key << std::endl;
    
    // Check for 'h' or 'H' (Heal)
    if ((key == 'h' || key == 'H') && currentTurn == WAITING_FOR_INPUT) {
        doHealing(foodHealing);
        std::cout << "[DEBUG] Key 'h' pressed. Transitioning to BOSS_ATTACKING." << std::endl;
        currentTurn = BOSS_ATTACKING;
        tickCounter = 0;
    }
    // Check for 'a' or 'A' (Attack)
    if ((key == 'a' || key == 'A') && currentTurn == WAITING_FOR_INPUT) {
        damageBoss(playerDamage + swordDamage);
        std::cout << "[DEBUG] Key 'a' pressed. Transitioning to BOSS_ATTACKING." << std::endl;
        currentTurn = BOSS_ATTACKING;
        tickCounter = 0;
    }
    // Check for 'd' or 'D' (Defend - placeholder)
    if ((key == 'd' || key == 'D') && currentTurn == WAITING_FOR_INPUT) {
        std::cout << "[DEBUG] Key 'd' pressed (defend action placeholder). Transitioning to BOSS_ATTACKING." << std::endl;
        // You can add defend logic here if desired.
        currentTurn = BOSS_ATTACKING;
        tickCounter = 0;
    }
}

