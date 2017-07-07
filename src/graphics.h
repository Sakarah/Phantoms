#ifndef GRAPHICS
#define GRAPHICS

#include "common.h"
#include <SFML/Graphics/VertexArray.hpp>

const int TILESET_ROW_SIZE = 8;

inline sf::IntRect rectForTilesetId(int id, int size = 1)
{
    return sf::IntRect(sf::Vector2i(id%TILESET_ROW_SIZE,id/TILESET_ROW_SIZE)*TILE_SIZE, sf::Vector2i(size,size)*TILE_SIZE);
}

void genSpriteVertices(sf::Vertex* out, sf::Vector2i spritePos, sf::IntRect spriteTexRect);
sf::VertexArray genBackgroundVertices(sf::Vector2u targetSize, std::pair<int,int> tileInfo);

inline int centerToSide(int centerPos, int size) { return centerPos-(size/2); }

#endif // GRAPHICS

