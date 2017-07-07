#include "Switch.h"
#include "../World.h"
#include "../../resources/AudioManager.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

Switch::Switch(ObjectSprite sprite, b2Vec2 pos) : Object(sprite, pos)
{
    _flags = ItemFlag;
}

void Switch::addLinkedObject(Object* obj)
{
    _linkedObjects.push_back(obj);
    obj->linkedSwitchActivated(isActive());
}

void Switch::addToWorld(World* world)
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
    b2PolygonShape squareShape;
    squareShape.SetAsBox(0.35, 0.45, b2Vec2(0.5,0.5), 0);
    fixDef.shape = &squareShape;
    fixDef.friction = 0.f;
    b2Fixture* fix = _physicBody->CreateFixture(&fixDef);

    b2Filter filter;
    filter.categoryBits = ItemFlag;
    filter.maskBits = CharacterFlag;
    fix->SetFilterData(filter);
}

void Switch::contactWith(Object* other)
{
    if(other->flags() & CharacterFlag)
    {
        _world->addPostStepAction([this]{setActive(!isActive());});
        AudioManager::playSound(AudioManager::Switch);
    }
}

void Switch::linkedSwitchActivated(bool active)
{
    // Linked switches are activated and deactivated together
    setActive(active);
}

bool Switch::isActive() { return _sprite == ObjectSprite::SwitchOn; }
void Switch::setActive(bool active)
{
    if(isActive() == active) return;
    _sprite = active ? ObjectSprite::SwitchOn : ObjectSprite::SwitchOff;

    for(Object* obj : _linkedObjects) obj->linkedSwitchActivated(active);
}
