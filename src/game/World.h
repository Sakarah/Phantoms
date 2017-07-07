#ifndef WORLD_H
#define WORLD_H

#include <list>
#include <functional>
#include <Box2D/Dynamics/b2World.h>
#include "ContactManager.h"
#include "common.h"
class Game;
class Object;
class Character;
class Path;
typedef std::function<void()> Action;

class World
{
public:
    World(Game*);
    ~World();
    void reset();

    LevelType levelType() const;
    void setLevelType(LevelType);
    b2Vec2 size() const;
    void setSize(b2Vec2);
    std::pair<int,int> backgroundInfo() const;
    void setBackgroundInfo(std::pair<int,int>);
    float speedFactor() const;
    void setSpeedFactor(float);
    float timeLeft() const;
    void setTimeLeft(float time);

    void addObject(Object*);
    void destroyObject(Object*);
    void destroyAllObjects(ObjectSprite type);
    const std::list<Object*>& getObjectList() const;
    Character* getCharacter(int playerId) const;

    void setCrystalPos(b2Vec2);
    void activateCrystal();

    Game* game() const;
    b2World* physicWorld();
    const b2World* physicWorld() const;

    void step();
    void checkWarp();
    void addPostStepAction(Action);
    void nextLevel();

private:
    Game* _game;
    float _speedFactor;
    b2World _physicWorld;
    ContactManager _contactManager;
    b2Vec2 _size;
    std::pair<int,int> _bgInfo;
    std::list<Object*> _objects;
    Character* _character[4];
    b2Vec2 _crystalPos;
    std::vector<Action> _postStepActions;
    bool _nextLevel;
    float _timeLeft;
};

#endif // WORLD_H
