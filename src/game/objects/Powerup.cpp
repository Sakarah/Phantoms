#include "Powerup.h"
#include "../World.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

Powerup::Powerup(ObjectSprite type, b2Vec2 pos) : Object(type, pos)
{
    _flags = ItemFlag;
    _lightRadius = 0.5;
    _lightColor = sf::Color::White;
    if(type == ObjectSprite::Coin || type == ObjectSprite::Coin2 || type == ObjectSprite::BlackCoin)
    {
        _flags |= CoinFlag;
        _lightColor = type != ObjectSprite::BlackCoin ? sf::Color(255,150,0) : sf::Color(70,0,255);
    }
    else if(type == ObjectSprite::Life) _lightColor = sf::Color(255,0,50);
}

void Powerup::addToWorld(World* world)
{
    _world = world;
    b2World* physicWorld = world->physicWorld();

    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.fixedRotation = true;
    bodyDef.position = _startPos;
    bodyDef.type = b2_staticBody;
    _physicBody = physicWorld->CreateBody(&bodyDef);

    b2FixtureDef fixDef;
    b2CircleShape circleShape;
    circleShape.m_p = b2Vec2(0.5, 0.5);
    if(_flags & CoinFlag) circleShape.m_radius = 0.25;
    else circleShape.m_radius = _sprite == ObjectSprite::Bomb ? 0.45 : 0.35;
    fixDef.shape = &circleShape;
    fixDef.isSensor = true;
    b2Fixture* fix = _physicBody->CreateFixture(&fixDef);

    b2Filter filter;
    filter.categoryBits = ItemFlag;
    filter.maskBits = CharacterFlag;
    fix->SetFilterData(filter);
}
