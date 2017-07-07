#include "graphics.h"

void genSpriteVertices(sf::Vertex* out, sf::Vector2i spritePos, sf::IntRect spriteTexRect)
{
    out[0].position = sf::Vector2f(spritePos.x, spritePos.y);
    out[0].texCoords = sf::Vector2f(spriteTexRect.left, spriteTexRect.top);

    out[1].position = sf::Vector2f(spritePos.x+spriteTexRect.width, spritePos.y);
    out[1].texCoords = sf::Vector2f(spriteTexRect.left+spriteTexRect.width, spriteTexRect.top);

    out[2].position = sf::Vector2f(spritePos.x+spriteTexRect.width, spritePos.y+spriteTexRect.height);
    out[2].texCoords = sf::Vector2f(spriteTexRect.left+spriteTexRect.width, spriteTexRect.top+spriteTexRect.height);

    out[3].position = sf::Vector2f(spritePos.x, spritePos.y+spriteTexRect.height);
    out[3].texCoords = sf::Vector2f(spriteTexRect.left, spriteTexRect.top+spriteTexRect.height);
}

sf::VertexArray genBackgroundVertices(sf::Vector2u targetSize, std::pair<int,int> tileInfo)
{
    sf::VertexArray bgVertices(sf::Quads);
    sf::IntRect bgTexRect = rectForTilesetId(tileInfo.first, tileInfo.second);

    int i = 0;
    for(unsigned y = 0 ; y < targetSize.y ; y += bgTexRect.height)
    {
        for(unsigned x = 0 ; x < targetSize.x ; x += bgTexRect.width)
        {
            bgVertices.resize(i+4);
            genSpriteVertices(&bgVertices[i], sf::Vector2i(x,y), bgTexRect);
            i += 4;
        }
    }

    return bgVertices;
}
