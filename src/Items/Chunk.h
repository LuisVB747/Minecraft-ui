#pragma once
#include "Block.h"
#include <vector>

/**
 * @class Chunk
 * @brief Represents a 16x16x16 block area in the world.
 */
class Chunk {
    private:
        std::vector<std::vector<std::vector<Block>>> blocks; // 16x16x16 grid of blocks
        public:
        /**
         * @brief Constructs a Chunk object.
         */
        Chunk();
    
        /**
         * @brief Gets the block at the specified position.
         * @param x The x-coordinate of the block.
         * @param y The y-coordinate of the block.
         * @param z The z-coordinate of the block.
         * @return The block at the specified position.
         */
        Block getBlock(int x, int y, int z) const;
    
        /**
         * @brief Sets the block at the specified position.
         * @param x The x-coordinate of the block.
         * @param y The y-coordinate of the block.
         * @param z The z-coordinate of the block.
         * @param block The block to set.
         */
        void setBlock(int x, int y, int z, Block block);
    };