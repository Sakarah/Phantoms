#include "Phantom.h"
#include "../../Random.h"
#include "../World.h"
#include "../gameplay.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

Phantom::Phantom(ObjectSprite type, b2Vec2 pos) : Object(type, pos)
{
    _flags = PhantomFlag;
}

void Phantom::addToWorld(World* world)
{
    _world = world;
    b2World* physicWorld = world->physicWorld();

    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.fixedRotation = true;
    bodyDef.position = _startPos;
    bodyDef.type = b2_dynamicBody;
    switch(_sprite)
    {
        case ObjectSprite::PhantomExplosive:
            _velocity = PHANTOM_EXPLOSIVE_SPEED*_world->speedFactor();
            bodyDef.linearVelocity = _velocity*getRandomDirection(false, true);
            break;
        case ObjectSprite::PhantomFast:
            _velocity = PHANTOM_FAST_SPEED*_world->speedFactor();
            bodyDef.linearVelocity = _velocity*getRandomDirection(true, false);
            break;
        case ObjectSprite::PhantomKiller:
            _velocity = PHANTOM_KILLER_SPEED*_world->speedFactor();
            break;
        case ObjectSprite::Phantom:
            _velocity = PHANTOM_SPEED*_world->speedFactor();
            bodyDef.linearVelocity = _velocity*getRandomDirection(true, true);
            break;
        default:
            _velocity = PHANTOM_SPEED*_world->speedFactor();
            break;
    }
    _physicBody = physicWorld->CreateBody(&bodyDef);

    b2FixtureDef fixDef;
    b2CircleShape circleShape;
    circleShape.m_p = b2Vec2(0.5, 0.5);
    circleShape.m_radius = 0.49;
    fixDef.shape = &circleShape;
    fixDef.friction = 0.f;
    fixDef.restitution = 1.f;

    b2Filter filter;
    filter.categoryBits = PhantomFlag;

    fixDef.isSensor = false;
    b2Fixture* solidFix = _physicBody->CreateFixture(&fixDef);
    filter.maskBits = WallFlag;
    solidFix->SetFilterData(filter);

    fixDef.isSensor = true;
    b2Fixture* sensorFix = _physicBody->CreateFixture(&fixDef);
    filter.maskBits = CharacterFlag;
    sensorFix->SetFilterData(filter);
}

void Phantom::contactWith(Object* other)
{
    if(other->flags() & WallFlag) _world->addPostStepAction([this]{simplifyMove();});
}

b2Vec2 Phantom::getRandomDirection(bool orthogonal, bool diagonal)
{
    if(!orthogonal && !diagonal) return b2Vec2(0,0);
    if(orthogonal && diagonal) orthogonal = Random::bernoulliTest();
    if(orthogonal)
    {
        if(Random::bernoulliTest()) return b2Vec2(Random::bernoulliTest() ? -1 : 1, 0);
        else return b2Vec2(0, Random::bernoulliTest() ? -1 : 1);
    }
    else
    {
        b2Vec2 dir(Random::bernoulliTest() ? -1 : 1, Random::bernoulliTest() ? -1 : 1);
        dir.Normalize();
        return dir;
    }
}
