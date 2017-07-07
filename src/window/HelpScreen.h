#ifndef HELPSCREEN_H
#define HELPSCREEN_H

#include "Screen.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Font.hpp>

class HelpScreen : public Screen
{
public:
    HelpScreen(Window*);
    ~HelpScreen() = default;
    void handleEvent(sf::Event&) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void updateSize() override;

private:
    void writeCenteredText(sf::String text, int size, int posY, sf::RenderTarget&, sf::RenderStates) const;

    sf::VertexArray _bgVertices;
    sf::Vector2f _topLeftOffset;
    int _currentPage;
};

#endif // HELPSCREEN_H
