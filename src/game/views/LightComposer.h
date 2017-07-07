#ifndef SHADOWS_H
#define SHADOWS_H

#include "LightSource.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class LightComposer : public sf::Drawable
{
public:
    enum RenderingFlags
    {
        None = 0x0,
        BlurWholeShadows = 0x1,
        IgnoreWalls = 0x2
    };

    LightComposer();
    void setView(const sf::Drawable*);
    void setFlags(RenderingFlags);
    void renderLights(sf::Vector2u size, const std::vector<LightSource>& lights, sf::Color ambientLight);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
    sf::RenderTexture _auxRenderTexture;
    sf::RenderTexture _viewRenderTexture;
    const sf::Drawable* _view;
    RenderingFlags _flags;
};

#endif // SHADOWS_H
