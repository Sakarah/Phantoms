#ifndef CHARACTER_H
#define CHARACTER_H

#include "Object.h"

class Character : public Object
{
public:
    Character(ObjectSprite sprite, b2Vec2 pos);
    ~Character() = default;
    void addToWorld(World*) override;
    void step(float time) override;
    void contactWith(Object* other) override;
    void giveInvincibility();
private:
    float _invincibilityTimeLeft;
};

#endif // CHARACTER_H
