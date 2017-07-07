#include "Background.h"
#include "../../graphics.h"
#include "../../resources/AssetManager.h"
#include <SFML/Graphics/RenderTarget.hpp>

Background::Background()
{
    _bgInfo = std::make_pair(-1,-1);
}

void Background::setBackground(sf::Vector2u size, std::pair<int,int> backgroundInfo)
{
    if(_size != size || _bgInfo != backgroundInfo)
    {
        _size = size;
        _bgInfo = backgroundInfo;
        _bgVertices = genBackgroundVertices(_size, _bgInfo);
    }
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = AssetManager::getTileset(AssetManager::Background);
    target.draw(_bgVertices, states);
}

Background::~Background()
{

}

