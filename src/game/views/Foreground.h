#ifndef FOREGROUND_H
#define FOREGROUND_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
class Game;

class Foreground : public sf::Drawable
{
public:
    Foreground(const Game*);
    ~Foreground() = default;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
    const Game* _game;
};

#endif // FOREGROUND_H
