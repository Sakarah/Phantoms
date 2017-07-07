#ifndef WALL_H
#define WALL_H

#include "Object.h"

class Wall : public Object
{
public:
    Wall(ObjectSprite sprite, b2Vec2 pos);
    ~Wall() = default;
    void addToWorld(World*) override;
    void linkedSwitchActivated(bool) override;
private:
    b2Fixture* createSquareFixture(b2Vec2 center, b2Vec2 halfSize = b2Vec2(0.5,0.5));
};

#endif // WALL_H
