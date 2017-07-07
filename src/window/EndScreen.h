#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include "Screen.h"
#include "../common.h"
#include <SFML/Graphics/Font.hpp>

class EndScreen : public Screen
{
public:
    EndScreen(GameEnd end, int score, Window* win);
    ~EndScreen() = default;
    void handleEvent(sf::Event&) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
    void drawCenteredText(sf::String text, sf::Font& font, int size, sf::Color color, int vPos, sf::RenderTarget&, sf::RenderStates) const;
    GameEnd _endType;
    int _score;
};

#endif // ENDSCREEN_H
