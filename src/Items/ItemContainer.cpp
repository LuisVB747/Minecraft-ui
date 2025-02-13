#include "ItemContainer.h"
ItemContainer::ItemContainer(int pX, int pY) {
    this->currentItem = Item();
    this->currentItemCount = 0;
    
    // Each container is 64x64 pixels.
    this->collider.height = 64;
    this->collider.width = 64;
    this->collider.setX(pX);
    this->collider.setY(pY);
    this->mouseHovering = false;
    this->hoverHighlighter.load("images/sprites/containerHover.png");
}

// Inventory = target container

void ItemContainer::leftSwapWith(ItemContainer& playerContainer) {
    //  The two interacting containers are empty. Do nothing.
    if (this->isEmpty() && playerContainer.isEmpty()) return;
    //  The items are the same, add them.
    if ((this->getCurrentItem() == playerContainer.getCurrentItem())) {
            // One of the containers is maxed. Swap the counts.
            if (this->isMaxed() || playerContainer.isMaxed()) {
                // Store one of the counts as a reference.
                int refCount = this->getItemCount();
                // Swap them.
                this->setItemCount(playerContainer.getItemCount());
                playerContainer.setItemCount(refCount);
            }else {
                // Add player's item count to the inventory container's count 
                int newItemCount = playerContainer.getItemCount() + this->getItemCount();
                // If it exceeds the stack limit, give the player container the rest.
                if (newItemCount > this->getCurrentItem().getMaxStack()) {
                    int residue = playerContainer.getItemCount() + this->getItemCount() - this->getCurrentItem().getMaxStack();
                    newItemCount = this->getCurrentItem().getMaxStack();
                    this->setItemCount(newItemCount);
                    playerContainer.setItemCount(residue);
                }else {
                    this->setItemCount(newItemCount);
                    playerContainer.empty();
                }
            }
    }
    // The items are different, swap the contents of the containers.
    else {
        // Store an item and count reference refence.
        Item itmRef = this->getCurrentItem();
        int countRef = this->getItemCount();
        // Swap both values.
        this->setCurrentItem(playerContainer.getCurrentItem());
        this->setItemCount(playerContainer.getItemCount());
        playerContainer.setCurrentItem(itmRef);
        playerContainer.setItemCount(countRef);
    }
};
void ItemContainer::rightSwapWith(ItemContainer& playerContainer) {
    if (playerContainer.isEmpty()) {
        // If the inventory container is empty, do nothing.
        if (this->isEmpty()) return;
        // If it's only one, simply pick it up.
        if (this->getItemCount() == 1) leftSwapWith(playerContainer);
        // It's more than one, pick up half of the items.
        else {
            int half = this->getItemCount()/2;
            this->setItemCount(this->getItemCount()-half);
            playerContainer.setItemCount(half);
            playerContainer.setCurrentItem(this->getCurrentItem());
        }
    }else {
        // If the inventory container is empty, place one item.
        if (this->isEmpty()) {
            this->setItemCount(1);
            this->setCurrentItem(playerContainer.getCurrentItem());
            // Deduct one from the player container.
            playerContainer.deductOne();
        }
        // If the target container has the same item as the player container, add one to it.
        else if (this->getCurrentItem() == playerContainer.getCurrentItem()) {
            // Check if adding one doesn't exceeds the items max stack size.
            if (!this->isMaxedAfter(1)) {
                this->setItemCount(this->getItemCount() + 1);
                // Deduct one from the player container. 
                playerContainer.deductOne();
            }
        }
    }
}
void ItemContainer::draw() {
    if (isMouseHovering()) { 
        this->hoverHighlighter.draw(this->collider.getMinX(),this->collider.getMinY());
    }
}
