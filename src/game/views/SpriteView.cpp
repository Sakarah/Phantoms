#include "SpriteView.h"
#include "../World.h"
#include "../objects/Object.h"
#include "../../graphics.h"
#include "../../resources/AssetManager.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

SpriteView::SpriteView(const World* world)
{
    _spriteFlags = AllFlags;
    _world = world;
}

void SpriteView::setSpriteFilter(uint16 flags)
{
    _spriteFlags = flags;
}

void SpriteView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::VertexArray spriteVertices(sf::Quads);
    int i = 0;
    for(Object* obj : _world->getObjectList())
    {
        if(!obj->isActive()) continue;
        if(!(obj->flags() & _spriteFlags)) continue;
        if(!obj->currentPos().IsValid()) continue;

        int objSpriteId = static_cast<int>(obj->sprite());
        int objSize = obj->flags() & BigSpriteFlag ? 2 : 1;
        sf::IntRect spriteTexRect = rectForTilesetId(objSpriteId, objSize);
        sf::Vector2i spritePos = obj->currentPixelPos();

        spriteVertices.resize(i+4);
        genSpriteVertices(&spriteVertices[i], spritePos, spriteTexRect);

        if(obj->flags() & SemiTransparentFlag)
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
