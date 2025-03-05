#include "BossState.h"

BossState::BossState(Player* player, ItemHandler* instantiatr) : State(player){
    this->instantiator = instantiator;
    this->background.load("images/states/bossState.png");
    this->SwordContainer = ItemContainer(99, 486);
    this->ShieldContainer = ItemContainer(221, 486);
    this->FoodContainer = ItemContainer(343,486);

    this->bossHealth = bossHealth;
    this->bossDamage = bossDamage;
    this->bossAccuracy = bossAccuracy;
};

