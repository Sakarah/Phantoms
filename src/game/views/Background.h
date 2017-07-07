#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class Background : public sf::Drawable
{
public:
    Background();
    ~Background();
    void setBackground(sf::Vector2u size, std::pair<int,int> bgInfo);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
    sf::Vector2u _size;
    std::pair<int,int> _bgInfo;
    sf::VertexArray _bgVertices;
};

#endif // BACKGROUND_H
