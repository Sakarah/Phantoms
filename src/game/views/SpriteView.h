#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include <SFML/Graphics/Drawable.hpp>
#include "../../common.h"
class World;

class SpriteView : public sf::Drawable
{
public:
    SpriteView(const World*);
    ~SpriteView() = default;
    void setSpriteFilter(uint16 flags);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
    const World* _world;
    uint16 _spriteFlags;
};

#endif // SPRITEVIEW_H
