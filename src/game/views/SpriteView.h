#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include <SFML/Graphics/Drawable.hpp>
#include "../../common.h"
class ObjectInfos;

class SpriteView : public sf::Drawable
{
public:
    SpriteView();
    ~SpriteView() = default;
    void setSpriteFilter(uint16 flags);
    void setObjectList(std::vector<ObjectInfos>&&);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
    std::vector<ObjectInfos> _objectList;
    uint16 _spriteFlags;
};

#endif // SPRITEVIEW_H
