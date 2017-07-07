#include "SpriteView.h"
#include "Frame.h"
#include "../../graphics.h"
#include "../../resources/AssetManager.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

SpriteView::SpriteView()
{
    _spriteFlags = AllFlags;
}

void SpriteView::setSpriteFilter(uint16 flags)
{
    _spriteFlags = flags;
}

void SpriteView::setObjectList(std::vector<ObjectInfos>&& objectList)
{
    _objectList = objectList;
}

void SpriteView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::VertexArray spriteVertices(sf::Quads, _objectList.size()*4);
    int i = 0;
    for(ObjectInfos objInfos : _objectList)
    {
        if(!(objInfos.flags & _spriteFlags)) continue;

        int objSpriteId = static_cast<int>(objInfos.sprite);
        int objSize = objInfos.flags & BigSpriteFlag ? 2 : 1;
        sf::IntRect spriteTexRect = rectForTilesetId(objSpriteId, objSize);
        sf::Vector2i spritePos = objInfos.pos;

        genSpriteVertices(&spriteVertices[i], spritePos, spriteTexRect);

        if(objInfos.flags & SemiTransparentFlag)
        {
            sf::Color semiTransparent = sf::Color(0xff,0xff,0xff,0x80);
            spriteVertices[i].color = semiTransparent;
            spriteVertices[i+1].color = semiTransparent;
            spriteVertices[i+2].color = semiTransparent;
            spriteVertices[i+3].color = semiTransparent;
        }

        i+=4;
    }
    states.texture = AssetManager::getTileset(AssetManager::Sprite);
    target.draw(spriteVertices, states);
}
