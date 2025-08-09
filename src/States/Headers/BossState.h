#pragma once
#include "State.h"
#include "ofImage.h"
#include "ArmorState.h"

/**
 * @class Boss
 * @brief Represents state where the boss starts  
 */
class BossState: public State {
    private:
        ofImage halfHeart; // Half heart of player
        ofImage halfHeartBoss; // Half heart of boss
        ofImage emptyHeart; // Empty heart of player and boss
        ArmorState* armorState; ///< Pointer to the armor state.
        ofImage bossImage;          // Normal boss image
        ofImage bossDamageImage;    // Boss damage effect image
        ofImage bossAttackImage;
        ofImage fullHeart;
        ofImage fullHeartBoss;
        bool isAttack;
        bool isDamaged;     // Tracks if the boss is in a damaged state
        float damageStartTime;  // Timer for showing the damage effect (in seconds)
        float damageDuration;  // Duration to show the damage image
    
        ItemHandler* instantiator; // pointer to the item
        ItemContainer SwordContainer; ///< Container that holds the Attacking item.
        ItemContainer ShieldContainer; ///<  Container that holds the Defensive item.
        ItemContainer FoodContainer; ///< Container that holds the healing item.
 
        
        void calculateSwordDamage(const std::string& swordName); // Calculate the damage of the sword
        void calculateHealing(const std::string& foodName); // Calculate the healing done by food

        int bossHealth; // Boss health
        int bossDamage; // Boss attack damage 
        int bossAccuracy; // Accuracy from boss' attacks

        int playerHealth; // Player health
        int playerDamage; // Player attack damage

        int swordDamage; // Adding for sword damage
        int foodHealing; // Adding for food healing
        int tickCounter;
        enum TurnState {
            WAITING_FOR_INPUT,
            PLAYER_ATTACKING,
            BOSS_ATTACKING,
            TURN_TRANSITION,
            GAME_OVER
        };
        TurnState currentTurn;
        TurnState lastTurn;
     

        void damagePlayer(int bossAccuracy); // Damage done to the player
        void damageBoss(int playerDamage); // Damage done to the boss

        void doHealing(int foodHealing); // Heals player when the button is pressed

        
        

    public:


        BossState(Player* player, ItemHandler* instantiator, ArmorState* armorState);


        void equipTools(Item newItem);


        bool canEquip(); 
        
        // Getters

        /**
         * @brief Gets the current boss health.
         * @return The current boss health.
         */
        int getBossHealth();

        /**
         * @brief Gets the current boss attack damage.
         * @return The current boss attack damage.
         */
        int getBossDamage();

        /**
         * @brief Gets the current boss attack accuracy.
         * @return The current boss accuracy.
         */
        int getBossAccuracy();

        /**
         * @brief Gets the current player health.
         * @return The current player health.
         */
        int getPlayerHealth();

        /**
         * @brief Gets the current player attack damage.
         * @return The current player attack damage.
         */
        int getPlayerDamage();

         /**
         * @brief Updates the state. Mandatory unused implementation.
         */
        void update();

        /**
         * @brief Draws the furnace state on the screen.
         */
        void draw();

        /**
         * @brief Handles mouse movement events.
         * @param x The x-coordinate of the mouse.
         * @param y The y-coordinate of the mouse.
         */
        void mouseMoved(int x, int y);

        /**
         * @brief Handles mouse press events.
         * @param x The x-coordinate of the mouse.
         * @param y The y-coordinate of the mouse.
         * @param button The mouse button that was pressed.
         */
        void mousePressed(int x, int y, int button);

        /**
         * @brief Handles key press events. Mandatory unused implementation.
         * @param key The key that was pressed.
         */
        void keyPressed(int key);


        


};