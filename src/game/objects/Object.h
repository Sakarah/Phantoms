#ifndef OBJECT_H
#define OBJECT_H

#include <Box2D/Dynamics/b2Body.h>
#include <SFML/Graphics/Color.hpp>
#include "../../common.h"

class World;
class Path;

class Object
{
public:
    Object(ObjectSprite sprite, b2Vec2 pos);
    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;
    virtual ~Object();

    virtual void addToWorld(World*) = 0;
    virtual void removeFromWorld();
    virtual void step(float time);
    virtual void contactWith(Object* other);
    virtual void linkedSwitchActivated(bool active);

    ObjectSprite sprite();
    uint16 flags();
    World* world();

    b2Vec2 currentPos();
    sf::Vector2i currentPixelPos();
    void jumpToPos(b2Vec2);
    void jumpToStartPos();
    void jumpToRandomPos();
    void move(b2Vec2 dir);
    void simplifyMove();
    float velocity();
    Path* path();
    void setPath(Path*);

    bool isActive();
    void setActive(bool);
    bool isDisabled() const;
    void disableUntilNextFrame();

    float lightRadius();
    sf::Color lightColor();

protected:
    ObjectSprite _sprite;
    uint16 _flags;
    World* _world;
    b2Body* _physicBody;
    b2Vec2 _startPos;
    float _velocity;
    Path* _path;
    float _lightRadius;
    sf::Color _lightColor;
};

#endif // OBJECT_H
