#pragma once
#include "State.h"


/**
 * @class Boss
 * @brief Represents state where the boss starts  
 */
class BossState: public State {
    private:

        ItemContainer SwordContainer; ///< Container that holds the Attacking item.
        ItemContainer ShieldContainer; ///<  Container that holds the Defensive item.
        ItemContainer FoodContainer; ///< Container that holds the healing item.
        
        vector<int> foodItems; ///< Holds the numbers of all food items that can heal you.


        int bossHealth; // Boss health
        int bossDamage; // Boss attack damage 
        int bossAccuracy; // Accuracy from boss' attacks
        

    public:


        BossState(Player* player, ItemHandler* instantiator);

        // Getters

        /**
         * @brief Gets the current boss health.
         * @return The current boss health.
         */
        int getBossHealth(){return this->bossHealth;}

        /**
         * @brief Gets the current boss attack damage.
         * @return The current boss attack damage.
         */
        int getBossDamage(){return this->bossDamage;}

        /**
         * @brief Gets the current boss attack accuracy.
         * @return The current boss accuracy.
         */
        int getBossAccuracy(){return this->bossAccuracy;}


        // Setters

        /**
         * @brief Sets the boss health 
         * @param bossHealth The bosses health
        */
        void setBossHealth(int bossHealth){this->bossHealth = bossHealth;}

        /**
         * @brief Sets the boss attack damage 
         * @param bossDamage The bosses attack damage
        */
        void setBossDamage(int bossDamage){this->bossDamage = bossDamage;}

        /**
         * @brief Sets the boss attack accuracy 
         * @param bossAccuracy The bosses attack accuracy
        */
        void setBossAccuracy(int bossAccuracy){this->bossAccuracy = bossAccuracy;}

         /**
         * @brief Updates the state. Mandatory unused implementation.
         */
        void update(){};

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
        void keyPressed(int key) {};


        


};