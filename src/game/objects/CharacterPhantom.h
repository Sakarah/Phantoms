#ifndef CHARACTERPHANTOM_H
#define CHARACTERPHANTOM_H

#include "Character.h"

class CharacterPhantom : public Character
{
public:
    CharacterPhantom(ObjectSprite sprite, b2Vec2 pos);
    ~CharacterPhantom() = default;
    void setBlackCrystalPos(b2Vec2);
    void addToWorld(World*) override;
    void contactWith(Object* other) override;
private:
    b2Vec2 _blackCrystalPos;
};

#endif // CHARACTERPHANTOM_H
