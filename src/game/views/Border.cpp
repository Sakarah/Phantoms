#include "Border.h"
#include "../../resources/AssetManager.h"
#include "../../graphics.h"
#include <SFML/Graphics/RenderTarget.hpp>

Border::Border()
{
    _vertices.setPrimitiveType(sf::Quads);
    _gameSize = sf::Vector2u(0,0);
    _winSize = sf::Vector2f(0,0);
}

void Border::setGameSize(sf::Vector2u gameSize)
{
    if(_gameSize != gameSize)
    {
        _gameSize = gameSize;
        genVertices();
    }
}

void Border::setWindowSize(sf::Vector2f winSize)
{
    int oldFrameWidth = getFrameWidth();
    _winSize = winSize;
    if(oldFrameWidth != getFrameWidth()) genVertices();
}

void Border::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = AssetManager::getTileset(AssetManager::Border);
    target.draw(_vertices, states);
}

int Border::getFrameWidth() const
{
    int xFrameWidth = _winSize.x-_gameSize.x;
    int yFrameWidth = _winSize.y-_gameSize.y;
    return std::max(xFrameWidth, yFrameWidth)/TILE_SIZE;
}

void Border::genVertices()
{
    if(_gameSize == sf::Vector2u(0,0)) return;

    sf::Vector2i gameTileSize = sf::Vector2i(_gameSize.x/TILE_SIZE, _gameSize.y/TILE_SIZE);

    _vertices.clear();
    int frameWidth = getFrameWidth();
    int i = 0;
    for(int radius = 1 ; radius <= frameWidth ; radius++)
    {
        // Generating the 4 corners
        _vertices.resize(i+16);
        genSpriteVertices(&_vertices[i], sf::Vector2i(-radius,-radius)*TILE_SIZE, rectForTilesetId(0));
        genSpriteVertices(&_vertices[i+4], sf::Vector2i(gameTileSize.x+radius-1,-radius)*TILE_SIZE, rectForTilesetId(3));
        genSpriteVertices(&_vertices[i+8], sf::Vector2i(-radius,gameTileSize.y+radius-1)*TILE_SIZE, rectForTilesetId(24));
        genSpriteVertices(&_vertices[i+12], sf::Vector2i(gameTileSize.x+radius-1,gameTileSize.y+radius-1)*TILE_SIZE, rectForTilesetId(27));
        i+=16;

        // Generating horizontal lines
        for(int x = -radius+1 ; x < gameTileSize.x/2 ; x++)
        {
            _vertices.resize(i+16);
            genSpriteVertices(&_vertices[i], sf::Vector2i(x,-radius)*TILE_SIZE, rectForTilesetId(1));
            genSpriteVertices(&_vertices[i+4], sf::Vector2i(gameTileSize.x-1-x,-radius)*TILE_SIZE, rectForTilesetId(2));
            genSpriteVertices(&_vertices[i+8], sf::Vector2i(x,gameTileSize.y+radius-1)*TILE_SIZE, rectForTilesetId(25));
            genSpriteVertices(&_vertices[i+12], sf::Vector2i(gameTileSize.x-1-x,gameTileSize.y+radius-1)*TILE_SIZE, rectForTilesetId(26));
            i+=16;
        }
        if(gameTileSize.x%2)
        {
            _vertices.resize(i+8);
            genSpriteVertices(&_vertices[i], sf::Vector2i(gameTileSize.x/2,-radius)*TILE_SIZE, rectForTilesetId(9));
            genSpriteVertices(&_vertices[i+4], sf::Vector2i(gameTileSize.x/2,gameTileSize.y+radius-1)*TILE_SIZE, rectForTilesetId(18));
            i+=8;
        }

        // Generating vertical lines
        for(int y = -radius+1 ; y < gameTileSize.y/2 ; y++)
        {
            _vertices.resize(i+16);
            genSpriteVertices(&_vertices[i], sf::Vector2i(-radius,y)*TILE_SIZE, rectForTilesetId(8));
            genSpriteVertices(&_vertices[i+4], sf::Vector2i(-radius,gameTileSize.y-1-y)*TILE_SIZE, rectForTilesetId(16));
            genSpriteVertices(&_vertices[i+8], sf::Vector2i(gameTileSize.x+radius-1,y)*TILE_SIZE, rectForTilesetId(11));
            genSpriteVertices(&_vertices[i+12], sf::Vector2i(gameTileSize.x+radius-1,gameTileSize.y-1-y)*TILE_SIZE, rectForTilesetId(19));
            i+=16;
        }
        if(gameTileSize.y%2)
        {
            _vertices.resize(i+8);
            genSpriteVertices(&_vertices[i], sf::Vector2i(-radius,gameTileSize.y/2)*TILE_SIZE, rectForTilesetId(17));
            genSpriteVertices(&_vertices[i+4], sf::Vector2i(gameTileSize.x+radius-1,gameTileSize.y/2)*TILE_SIZE, rectForTilesetId(10));
            i+=8;
        }
    }
}

Border::~Border()
{
    //
}
