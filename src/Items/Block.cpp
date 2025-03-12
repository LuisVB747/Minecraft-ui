#include "Block.h"

// Default constructor (air block)
Block::Block() : type(0), color(Color(255, 255, 255)) {}

// Parameterized constructor
Block::Block(int type) : type(type) {
    // Set block color based on type
    switch (type) {
        case 0: // Air
            color = Color(255, 255, 255); // White (invisible)
            break;
        case 1: // Stone
            color = Color(128, 128, 128); // Gray
            break;
        case 2: // Grass
            color = Color(0, 255, 0); // Green
            break;
        case 3: // Dirt
            color = Color(139, 69, 19); // Brown
            break;
        case 4: // Wood
            color = Color(139, 69, 19); // Brown
            break;
        default:
            color = Color(255, 0, 255); // Magenta (unknown block type)
            break;
    }
}

int Block::getType() const {
    return type;
}

Color Block::getColor() const {
    return color;
}

void Block::setType(int type) {
    this->type = type;
    // Update color when type changes
    switch (type) {
        case 0: // Air
            color = Color(255, 255, 255); // White
            break;
        case 1: // Stone
            color = Color(128, 128, 128); // Gray
            break;
        case 2: // Grass
            color = Color(0, 255, 0); // Green
            break;
        case 3: // Dirt
            color = Color(139, 69, 19); // Brown
            break;
        case 4: // Wood
            color = Color(139, 69, 19); // Brown
            break;
        default:
            color = Color(255, 0, 255); // Magenta (unknown block type)
            break;
    }
}

void Block::setColor(Color color) {
    this->color = color;
}