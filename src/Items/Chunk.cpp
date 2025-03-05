#include "Chunk.h"

Chunk::Chunk() {
    blocks.resize(16, std::vector<std::vector<Block>>(16, std::vector<Block>(16))); // Initialize 16x16x16 grid of air blocks
}

Block Chunk::getBlock(int x, int y, int z) const{
    if(x>=0 && x < 16 && y >= 0 && y < 16 && z>=0 && z < 16){
        return blocks[x][y][z];
    }
    return Block();
}
void Chunk::setBlock(int x, int y, int z, Block block) {
    if (x >= 0 && x < 16 && y >= 0 && y < 16 && z >= 0 && z < 16) {
        blocks[x][y][z] = block;
    }
}