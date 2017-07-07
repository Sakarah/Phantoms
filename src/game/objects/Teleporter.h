#ifndef TELEPORTER_H
#define TELEPORTER_H

#include "Object.h"

class Teleporter : public Object
{
public:
    Teleporter(ObjectSprite sprite, b2Vec2 pos);
    ~Teleporter() = default;
    void setDestination(b2Vec2);
    void addToWorld(World*) override;
    void contactWith(Object*) override;
private:
    b2Vec2 _destination;
};

#endif // TELEPORTER_H
