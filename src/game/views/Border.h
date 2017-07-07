#ifndef BORDER_H
#define BORDER_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class Border : public sf::Drawable
{
public:
    Border();
    ~Border();
    void setGameSize(sf::Vector2u);
    void setWindowSize(sf::Vector2f);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
    int getFrameWidth() const;
    void genVertices();

    sf::Vector2u _gameSize;
    sf::Vector2f _winSize;
    sf::VertexArray _vertices;
};

#endif // BORDER_H
