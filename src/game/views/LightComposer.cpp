#include "LightComposer.h"
#include "../../resources/AssetManager.h"
#include <SFML/Graphics/Sprite.hpp>

LightComposer::LightComposer()
{
    _view = nullptr;
    _flags = None;
}

void LightComposer::setView(const sf::Drawable* view)
{
    _view = view;
}

void LightComposer::setFlags(RenderingFlags flags)
{
    _flags = flags;
}

void LightComposer::renderLights(sf::Vector2u size, const std::vector<LightSource>& lightSources, sf::Color ambientLight)
{
    if(size != _auxRenderTexture.getSize())
    {
        _auxRenderTexture.create(size.x, size.y);
        _viewRenderTexture.create(size.x, size.y);
    }

    sf::Shader* lightAttenuation = AssetManager::getShader(AssetManager::LightAttenuation);
    sf::RenderTexture* lightMaskTexture = _flags & BlurWholeShadows ? &_viewRenderTexture : &_auxRenderTexture;
    lightMaskTexture->clear(ambientLight);
    for(LightSource light : lightSources)
    {
        sf::VertexArray lightVertices = _flags & IgnoreWalls ? light.passingWallsVertices() : light.lightVertices();

        lightAttenuation->setUniform("center", toGLCoords(toScreenPos(light.center()), size));
        lightAttenuation->setUniform("radius", TILE_SIZE*light.radius());
        lightAttenuation->setUniform("color", sf::Glsl::Vec4(light.color()));

        sf::RenderStates lightTextureStates;
        lightTextureStates.blendMode = sf::BlendAdd;
        lightTextureStates.shader = lightAttenuation;

        lightMaskTexture->draw(lightVertices, lightTextureStates);
    }
    lightMaskTexture->display();

    sf::RenderStates lightMaskStates;
    lightMaskStates.blendMode = sf::BlendMultiply;

    if(_flags & BlurWholeShadows)
    {
        sf::Shader* blur = AssetManager::getShader(AssetManager::Blur);
        blur->setUniform("source", sf::Shader::CurrentTexture);
        blur->setUniform("blur_offset", sf::Glsl::Vec2(1./size.x, 0));
        sf::RenderStates auxBlurStates;
        auxBlurStates.blendMode = sf::BlendNone;
        auxBlurStates.shader = blur;

        _auxRenderTexture.draw(sf::Sprite(lightMaskTexture->getTexture()), auxBlurStates);
        _auxRenderTexture.display();

        blur->setUniform("blur_offset", sf::Glsl::Vec2(0, 1./size.y));
        lightMaskStates.shader = blur;
    }

    _viewRenderTexture.clear(sf::Color(0,0,0,0));
    _viewRenderTexture.draw(*_view);
    _viewRenderTexture.draw(sf::Sprite(_auxRenderTexture.getTexture()), lightMaskStates);
    _viewRenderTexture.display();
}

void LightComposer::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(sf::Sprite(_viewRenderTexture.getTexture()), states);
}
