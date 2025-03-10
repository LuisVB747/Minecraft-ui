#pragma once


struct Color{
    int r,g,b;
    Color(): r(255), g(255), b(255) {}

    Color(int r, int g, int b):
    r(r), g(g), b(b) {}
};

class Block{
private:
    int type; //Block type
    Color color; //Block color for rendering

public:
Block();

/**
 * @brief Constructs a block with the specified type.
 * @param type The type of the block.
 */
Block(int type);

/**
 * @brief Gets the type of the block.
 * @return The block type.
 */
int getType() const;

/**
 * @brief Gets the color of the block.
 * @return The block color.
 */
Color getColor() const;

/**
 * @brief Sets the type of the block.
 * @param type The new block type.
 */
void setType(int type);

/**
 * @brief Sets the color of the block.
 * @param color The new block color.
 */
void setColor(Color color);

};