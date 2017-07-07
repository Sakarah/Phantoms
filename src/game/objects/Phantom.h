#ifndef PHANTOM_H
#define PHANTOM_H

#include "Object.h"

class Phantom : public Object
{
public:
    Phantom(ObjectSprite sprite, b2Vec2 pos);
    ~Phantom() = default;
    void addToWorld(World*) override;
    void contactWith(Object*) override;
private:
    static b2Vec2 getRandomDirection(bool orthogonal, bool diagonal);
};

#endif // PHANTOM_H
