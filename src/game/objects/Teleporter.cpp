#include "Teleporter.h"
#include "../World.h"
#include "../../resources/AudioManager.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

Teleporter::Teleporter(ObjectSprite type, b2Vec2 pos) : Object(type, pos)
{
    _flags = ItemFlag | NeverDisabledFlag;
}

void Teleporter::setDestination(b2Vec2 dest)
{
    _destination = dest;
}

void Teleporter::addToWorld(World* world)
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
    circleShape.m_radius = 0.5;
    fixDef.shape = &circleShape;
    fixDef.isSensor = true;
    b2Fixture* fix = _physicBody->CreateFixture(&fixDef);

    b2Filter filter;
    filter.categoryBits = ItemFlag;
    filter.maskBits = CharacterFlag;
    fix->SetFilterData(filter);
}

void Teleporter::contactWith(Object* other)
{
    if(other->flags() & CharacterFlag)
    {
        _world->addPostStepAction([this, other]{other->jumpToPos(_destination);});
        AudioManager::playSound(AudioManager::Teleport);
    }
}
