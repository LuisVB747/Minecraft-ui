#pragma once
#include "State.h"


/**
 * @class Boss
 * @brief Represents state where the boss starts  
 */
class BossState: public State {
    private:
        ItemHandler* instantiator; // pointer to the item
        ItemContainer SwordContainer; ///< Container that holds the Attacking item.
        ItemContainer ShieldContainer; ///<  Container that holds the Defensive item.
        ItemContainer FoodContainer; ///< Container that holds the healing item.
        
        vector<int> foodItems; ///< Holds the numbers of all food items that can heal you.


        int bossHealth; // Boss health
        int bossDamage; // Boss attack damage 
        int bossAccuracy; // Accuracy from boss' attacks
        

    public:


        BossState(Player* player, ItemHandler* instantiator);

        void equipTools(Item newItem);


        bool canEquip(); 
        
        // Getters

        /**
         * @brief Gets the current boss health.
         * @return The current boss health.
         */
        int getBossHealth();//return this->bossHealth;}

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