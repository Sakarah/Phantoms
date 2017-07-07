#ifndef POWERUP_H
#define POWERUP_H

#include "Object.h"

class Powerup : public Object
{
public:
    Powerup(ObjectSprite sprite, b2Vec2 pos);
    ~Powerup() = default;
    void addToWorld(World*) override;
};

#endif // POWERUP_H
