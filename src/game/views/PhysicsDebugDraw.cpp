#include "PhysicsDebugDraw.h"
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

PhysicsDebugDraw::PhysicsDebugDraw()
{
    _world = nullptr;
    SetFlags(e_shapeBit | e_jointBit /*| e_aabbBit*/);
}

void PhysicsDebugDraw::setupDebugDraw(World* w)
{
    _world = w;
    _world->physicWorld()->SetDebugDraw(this);
}

void PhysicsDebugDraw::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!_world) return;

    _renderTarget = &target;
    _renderStates = states;
    _world->physicWorld()->DrawDebugData();
}

void PhysicsDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape polygon(vertexCount);
    for(int i = 0 ; i < vertexCount ; i++) polygon.setPoint(i, toScreenPos(vertices[i]));
    polygon.setOutlineColor(sf::Color(color.r, color.g, color.b, 0xa0));
    polygon.setOutlineThickness(1);
    polygon.setFillColor(sf::Color::Transparent);
    _renderTarget->draw(polygon, _renderStates);
}

void PhysicsDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape polygon(vertexCount);
    for(int i = 0 ; i < vertexCount ; i++) polygon.setPoint(i, toScreenPos(vertices[i]));
    polygon.setFillColor(sf::Color(color.r, color.g, color.b, 0x80));
    _renderTarget->draw(polygon, _renderStates);
}

void PhysicsDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    sf::CircleShape circle;
    circle.setPosition(toScreenPos(center - radius*b2Vec2(1,1)));
    circle.setRadius(radius*TILE_SIZE);
    circle.setOutlineColor(sf::Color(color.r, color.g, color.b, 0xa0));
    circle.setOutlineThickness(1);
    circle.setFillColor(sf::Color::Transparent);
    _renderTarget->draw(circle, _renderStates);
}

void PhysicsDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2&, const b2Color& color)
{
    sf::CircleShape circle;
    circle.setPosition(toScreenPos(center - radius*b2Vec2(1,1)));
    circle.setRadius(radius*TILE_SIZE);
    circle.setFillColor(sf::Color(color.r, color.g, color.b, 0x80));
    _renderTarget->draw(circle, _renderStates);
}

void PhysicsDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    sf::ConvexShape polygon(2);
    polygon.setPoint(0, toScreenPos(p1));
    polygon.setPoint(1, toScreenPos(p2));
    polygon.setOutlineColor(sf::Color(color.r, color.g, color.b, 0xa0));
    polygon.setOutlineThickness(1);
    polygon.setFillColor(sf::Color::Transparent);
    _renderTarget->draw(polygon, _renderStates);
}

void PhysicsDebugDraw::DrawTransform(const b2Transform& xf)
{
    B2_NOT_USED(xf);
    // Don't know how to draw that...
}
