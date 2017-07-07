#ifndef SWITCH_H
#define SWITCH_H

#include "Object.h"

class Switch : public Object
{
public:
    Switch(ObjectSprite sprite, b2Vec2 pos);
    ~Switch() = default;
    void addLinkedObject(Object*);
    bool isActive();
    void setActive(bool);
    void addToWorld(World*) override;
    void contactWith(Object*) override;
    void linkedSwitchActivated(bool) override;
private:
    std::vector<Object*> _linkedObjects;
};

#endif // SWITCH_H
