#include "CraftingState.h"

CraftingState::CraftingState(Player* player, ItemHandler* instantce) : State(player) {
    this->instantiator = instantce;
    this->background.load("images/states/crafting.png");
    this->resultContainer = ItemContainer(496,139);
    // Offsets were obtained via MsPaint. Check the lower left corner of the window for the x, y coords. Also try Piskel.
    const int VERTICAL_OFFSET = 68;
    const int HORIZONTAL_OFFSET = 120;
    const int DISTANCE_BETWEEN_CONTAINERS = 72;
    const int ROWS = 3;
    const int COLS = 3;
    for (int y = VERTICAL_OFFSET; y < VERTICAL_OFFSET + (DISTANCE_BETWEEN_CONTAINERS*ROWS); y = y + DISTANCE_BETWEEN_CONTAINERS) {
        for (int x = HORIZONTAL_OFFSET; x < HORIZONTAL_OFFSET + (DISTANCE_BETWEEN_CONTAINERS*COLS); x = x + DISTANCE_BETWEEN_CONTAINERS) {
            // Create an empty container at x, y
            this->craftingGrid.push_back(ItemContainer(x,y));
        }
    }
};

void CraftingState::craft() {
    vector<int> translatedGrid;
    // Interpret the ItemContainer grid as an array of integers
    for (ItemContainer container : craftingGrid) {
        translatedGrid.push_back(container.getCurrentItem().getItemNumber());
    }
    // Remove any empty rows/columns
    standarizeGrid(translatedGrid);
    pair<Item, int> result = getItemFromRecipie(translatedGrid);
    Item resultItem = result.first;
    int resultItemCount = result.second;
    if (resultItemCount == 0) return; // No recipie was found, do nothing.
    if (resultContainer.isEmpty())
        {
            resultContainer.setCurrentItem(resultItem);
            resultContainer.setItemCount(resultItemCount);
        }
    else if (resultContainer.getCurrentItem() == resultItem && !resultContainer.isMaxedAfter(resultItemCount))
        {
            resultContainer.setCurrentItem(resultItem);
            resultContainer.setItemCount(resultContainer.getItemCount()+resultItemCount);
        }
    // The result container is either full or it has a different crafted item already, do nothing. 
    else {return;} 
    // Deduct one from all the ingredients
    for (ItemContainer& ingredient : craftingGrid) { ingredient.deductOne(); }
}

void CraftingState::draw() {
    background.draw(0,0);
    for (auto slot : this->craftingGrid) {
        slot.draw();
    }
    this->resultContainer.draw();
    this->getPlayer()->draw();
};
void CraftingState::mouseMoved(int x, int y) {
    State::mouseMoved(x,y);
    // Check if the mouse enters any of the state's containers
    for (auto& slot : this->craftingGrid) { slot.mouseEntered(x,y); }
    this->resultContainer.mouseEntered(x,y);
};
void CraftingState::mousePressed(int x, int y, int button) {
    State::mousePressed(x,y,button);
    if (button == 0) {
        for (auto& slot : this->craftingGrid) { slot.leftMouseClicked(x,y,getPlayer()->getCursorContainer()); }
        // Only allow the player to left click if thier mouse(container) isn't holding an item already.
        if (this->getPlayer()->getCursorContainer().isEmpty()) this->resultContainer.leftMouseClicked(x,y,this->getPlayer()->getCursorContainer());
    }
    if (button == 2) {
        for (auto& slot : this->craftingGrid) { slot.rightMouseClicked(x,y,getPlayer()->getCursorContainer()); }
        // Only allow the player to right click if thier mouse(container) isn't holding an item already.
        if (this->getPlayer()->getCursorContainer().isEmpty()) this->resultContainer.rightMouseClicked(x,y,this->getPlayer()->getCursorContainer());
    }
};

void CraftingState::standarizeGrid(vector<int>& grid) {
    for (int i = 0; i < 2; i++) {
        // Vertical line checker
        // If theres is a line, move columns left. Do this a maximum of two times.
        if (grid[0] == 0 && grid[3] == 0 && grid[6] == 0) {
            grid[0] = grid[1];
            grid[1] = grid[2];
            grid[2] = 0;
            grid[3] = grid[4];
            grid[4] = grid[5];
            grid[5] = 0;
            grid[6] = grid[7];
            grid[7] = grid[8];
            grid[8] = 0;
        } 
    }
     for (int i = 0; i < 2; i++) {
        // Horizontal line checker
        // If theres is a line, move rows up. Do this a maximum of two times.
        if (grid[0] == 0 && grid[1] == 0 && grid[2] == 0) {
                grid[0] = grid[3];
                grid[1] = grid[4];
                grid[2] = grid[5];
                grid[3] = grid[6];
                grid[4] = grid[7];
                grid[5] = grid[8];
                grid[6] = 0;
                grid[7] = 0;
                grid[8] = 0;
        } 
    }
}

pair<Item, int> CraftingState::getItemFromRecipie(vector<int> grid) {
    // A pair allows us to hold two types of data in one variable.
    // In this case, we are holding an Item and the amount of that item that the crafting recipie produces.
    pair<Item, int> result;
    // Initialize the recipie to Item() and 0, indicating that no recipie has yet been found.
    result.first = Item();
    result.second = 0;

    /*The syntax is as follows:
        if (grid == vector<int>
                {#, #, #,
                 #, #, #,
                 #, #, #}
        ) { 
            result.first = instantiator->getItemFromNumber(itemNumber);
            result.second = itemAmount;
        }
       Make sure to align the recipie to the upper left corner of the array.
       Example {#, #, #,
                 #, #, #,
                 #, #, 1}
                would be ->
                {1, #, #,
                 #, #, #,
                 #, #, #}
    */
        if (grid == vector<int> // Plank
                {2, 0, 0,
                 0, 0, 0,
                 0, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(3);
            result.second = 4;
        }
        if (grid == vector<int> // Stick
                {3, 0, 0,
                 3, 0, 0,
                 0, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(4);
            result.second = 4;
        }
        if (grid == vector<int> // Wooden pickaxe
                {3, 3, 3,
                 0, 4, 0,
                 0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(5);
            result.second = 1;
        }
        if (grid == vector<int> // stone pickaxe
                {30, 30, 30,
                 0, 4, 0,
                 0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(6);
            result.second = 1;
        }
        if (grid == vector<int> // Iron pickaxe
                {34, 34, 34,
                 0, 4, 0,
                 0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(7);
            result.second = 1;
        }
        if (grid == vector<int> // Diamond pickaxe
                {36, 36, 36,
                 0, 4, 0,
                 0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(8);
            result.second = 1;
        }
        if (grid == vector<int> // Gold pickaxe
                {35, 35, 35,
                 0, 4, 0,
                 0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(9);
            result.second = 1;
        }
        if (grid == vector<int> // Wooden shovel
                {3, 0, 0,
                4, 0, 0,
                4, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(10);
            result.second = 1;
        }
        if (grid == vector<int> // Stone shovel
                {30, 0, 0,
                4, 0, 0,
                4, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(11);
            result.second = 1;
        }
        if (grid == vector<int> // Iron shovel
                {34, 0, 0,
                4, 0, 0,
                4, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(12);
            result.second = 1;
        }
        if (grid == vector<int> // Diamond shovel
                {36, 0, 0,
                4, 0, 0,
                4, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(13);
            result.second = 1;
        }
        if (grid == vector<int>  // Gold shovel
                {35, 0, 0,
                4, 0, 0,
                4, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(14);
            result.second = 1;
        }
        if (grid == vector<int> // Wooden sword
                {3, 0, 0,
                3, 0, 0,
                4, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(15);
            result.second = 1;
        }
        if (grid == vector<int> // Stone sword
                {30, 0, 0,
                30, 0, 0,
                4, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(16);
            result.second = 1;
        }
        if (grid == vector<int> // Iron sword
                {34, 0, 0,
                34, 0, 0,
                4, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(17);
            result.second = 1;
        }
        if (grid == vector<int>  // Diamond sword
                {36, 0, 0,
                36, 0, 0,
                4, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(18);
            result.second = 1;
        }
        if (grid == vector<int> // Gold sword
                {35, 0, 0,
                35, 0, 0,
                4, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(19);
            result.second = 1;
        }
        if (grid == vector<int> // Wooden axe
                {3, 3, 0,
                3, 4, 0,
                0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(20);
            result.second = 1;
        }
        if (grid == vector<int> // Stone axe
                {30, 30, 0,
                30, 4, 0,
                0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(21);
            result.second = 1;
        }
        if (grid == vector<int> // Iron axe
                {34, 34, 0,
                34, 4, 0,
                0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(22);
            result.second = 1;
        }
        if (grid == vector<int> // Diamond axe
                {36, 36, 0,
                36, 4, 0,
                0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(23);
            result.second = 1;
        }
        if (grid == vector<int>  // Gold axe
                {35, 35, 0,
                35, 4, 0,
                0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(24);
            result.second = 1;
        }
        if (grid == vector<int> // Wooden aoe
                {3, 3, 0,
                0, 4, 0,
                0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(25);
            result.second = 1;
        }
        if (grid == vector<int> // Stone hoe
                {30, 30, 0,
                0, 4, 0,
                0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(26);
            result.second = 1;
        }
        if (grid == vector<int> // Iron hoe
                {34, 34, 0,
                0, 4, 0,
                0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(27);
            result.second = 1;
        }
        if (grid == vector<int> // Diamond hoe
                {36, 63, 0,
                0, 4, 0,
                0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(28);
            result.second = 1;
        }
        if (grid == vector<int> // Gold hoe
                {35, 35, 0,
                0, 4, 0,
                0, 4, 0}
            ) {
            result.first = instantiator->getItemFromNumber(29);
            result.second = 1;
        }
        if (grid == vector<int> // Beacon
                {0, 0, 0,
                0, 0, 0,
                0, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(42);
            result.second = 1;
        }
        if (grid == vector<int> // Eye of ender
                {49, 48, 0,
                0, 0, 0,
                0, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(50);
            result.second = 1;
        }
        if (grid == vector<int> // Bread
                {51, 51, 51,
                0, 0, 0,
                0, 0, 0}
            ) {
            result.first = instantiator->getItemFromNumber(52);
            result.second = 1;
        }
        if (grid == vector<int> // Golden apple
                {35, 35, 35,
                35, 54, 35,
                35, 35, 35}
            ) {
            result.first = instantiator->getItemFromNumber(56);
            result.second = 1;
        } 
        return result;    
}


