#ifndef FOREGROUND_H
#define FOREGROUND_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Frame.h"

class Foreground : public sf::Drawable
{
public:
    Foreground();
    ~Foreground() = default;
    void setGameInfos(GameInfos&&);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
    GameInfos _gameInfos;
};

#endif // FOREGROUND_H
