#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "../../common.h"
#include <SFML/Graphics/VertexArray.hpp>
class b2World;

class LightSource
{
public:
    LightSource(b2Vec2 pos, float radius, sf::Color color);
    void computeLight(const b2World* world);

    b2Vec2 pos();
    b2Vec2 center();
    float radius();
    sf::Color color();
    const sf::VertexArray& lightVertices();
    sf::VertexArray passingWallsVertices();

private:
    b2Vec2 _pos;
    float _radius;
    sf::Color _color;
    sf::VertexArray _lightVertices;
};

#endif // LIGHTSOURCE_H
