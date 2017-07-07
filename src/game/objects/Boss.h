#ifndef BOSS_H
#define BOSS_H

#include "Object.h"
class Powerup;

class Boss : public Object
{
public:
    Boss(ObjectSprite sprite, b2Vec2 pos);
    ~Boss() = default;
    void setSword(Powerup*);
    void addToWorld(World*) override;
    void step(float time) override;
    void contactWith(Object*) override;
private:
    int _nbLives;
    float _timeLeftBeforeSpawn;
    Powerup* _sword;
};

#endif // BOSS_H
