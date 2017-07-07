#include "Object.h"
#include "../../Random.h"
#include "../gameplay.h"
#include "../World.h"
#include "../EmptySpaceChecker.h"
#include "../paths/Path.h"
#include <Box2D/Dynamics/b2World.h>

Object::Object(ObjectSprite type, b2Vec2 pos)
{
    _sprite = type;
    _flags = NoFlag;
    _startPos = pos;
    _world = nullptr;
    _physicBody = nullptr;
    _path = nullptr;
    _lightRadius = 0;
}

void Object::removeFromWorld()
{
    if(!_physicBody) return;
    _physicBody->GetWorld()->DestroyBody(_physicBody);
    _world = nullptr;
    _physicBody = nullptr;
}

void Object::step(float time)
{
    if(!_path) return;
    _path->step(time);
}

void Object::contactWith(Object*)
{
    // Par défaut : Aucune action au contact
}

void Object::linkedSwitchActivated(bool)
{
    // Par défaut : Aucune action à la (dés)activation d'un interrupteur lié
}

ObjectSprite Object::sprite() { return _sprite; }
uint16 Object::flags() { return _flags; }
b2Vec2 Object::currentPos() { return _physicBody ? _physicBody->GetPosition() : b2Vec2(); }
sf::Vector2i Object::currentPixelPos() { return toPixelPos(currentPos()); }

World* Object::world() { return _world; }

void Object::jumpToPos(b2Vec2 pos)
{
    if(!_physicBody) return;
    _physicBody->SetTransform(pos, 0);
}

void Object::jumpToStartPos()
{
    jumpToPos(_startPos);
    if(_path) _path->reset();
}

void Object::jumpToRandomPos()
{
    b2Vec2 pos;
    bool valid = false;
    while(!valid)
    {
        pos = b2Vec2(Random::genUniformFloat(0, _world->size().x-1), Random::genUniformFloat(0, _world->size().y-1));

        b2AABB queryAABB;
        queryAABB.lowerBound = pos+b2Vec2(0.375,0.375);
        queryAABB.upperBound = pos+b2Vec2(0.875,0.875);

        EmptySpaceChecker spaceChecker(AllFlags);
        _world->physicWorld()->QueryAABB(&spaceChecker, queryAABB);
        valid = spaceChecker.isEmpty();
    }

    jumpToPos(pos);
}

void Object::move(b2Vec2 dir)
{
    if(!_physicBody) return;
    dir.Normalize();
    _physicBody->SetLinearVelocity(_velocity*dir);
}

void Object::simplifyMove()
{
    b2Vec2 velocity = _physicBody->GetLinearVelocity();
    velocity.x = velocity.x > 0+MIN_VELOCITY ? 1 : velocity.x < 0-MIN_VELOCITY ? -1 : 0;
    velocity.y = velocity.y > 0+MIN_VELOCITY ? 1 : velocity.y < 0-MIN_VELOCITY ? -1 : 0;
    move(velocity);
}

float Object::velocity() { return _velocity; }

Path* Object::path() { return _path; }
void Object::setPath(Path* path)
{
    if(_path) delete _path;
    if(path) path->setObject(this);
    _path = path;
}

bool Object::isActive() { return _physicBody->IsActive(); }
void Object::setActive(bool active) { _physicBody->SetActive(active); }

// Permet d'éviter les actions multiples sur un même objet. Un objet désactivé ne génère plus de collisions.
bool Object::isDisabled() const { return _flags & DisabledFlag; }
void Object::disableUntilNextFrame()
{
    if(_flags & NeverDisabledFlag) return;

    _flags |= DisabledFlag;
    _world->addPostStepAction([this]{ _flags &= ~DisabledFlag; });
}

float Object::lightRadius() { return _lightRadius; }
sf::Color Object::lightColor() { return _lightColor; }

Object::~Object()
{
    if(_path) delete _path;
}
