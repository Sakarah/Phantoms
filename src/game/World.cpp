#include "World.h"
#include "objects/Object.h"
#include "objects/Character.h"
#include "objects/Powerup.h"
#include "Game.h"
#include "gameplay.h"
#include "WarpChecker.h"
#include "../resources/AudioManager.h"
#include "../resources/Settings.h"

World::World(Game* game) : _physicWorld(b2Vec2(0,0))
{
    _game = game;
    _physicWorld.SetContactListener(&_contactManager);
}

void World::reset()
{
    for(Object* obj : _objects)
    {
        obj->removeFromWorld();
        delete obj;
    }
    _objects.clear();
    _timeLeft = 1.f;
    for(int i = 0 ; i < 4 ; i++) _character[i] = nullptr;
    _nextLevel = false;
}

b2Vec2 World::size() const { return _size; }
void World::setSize(b2Vec2 size) { _size = size; }
std::pair<int,int> World::backgroundInfo() const { return _bgInfo; }
void World::setBackgroundInfo(std::pair<int,int> bgInfo) { _bgInfo = bgInfo; }
float World::speedFactor() const { return _speedFactor; }
void World::setSpeedFactor(float speed) { _speedFactor = speed; }
float World::timeLeft() const { return _timeLeft; }
void World::setTimeLeft(float time) { _timeLeft = time/_speedFactor; }

void World::addObject(Object* obj)
{
    obj->addToWorld(this);
    _objects.push_back(obj);

    if(obj->sprite() == ObjectSprite::Character1) _character[0] = static_cast<Character*>(obj);
    else if(obj->sprite() == ObjectSprite::Character2) _character[1] = static_cast<Character*>(obj);
    else if(obj->sprite() == ObjectSprite::Character3) _character[2] = static_cast<Character*>(obj);
    else if(obj->sprite() == ObjectSprite::Character4) _character[3] = static_cast<Character*>(obj);
    else if(obj->sprite() == ObjectSprite::PhantomPlayer) _character[1] = static_cast<Character*>(obj);
}

void World::destroyObject(Object* obj)
{
    obj->removeFromWorld();
    _objects.remove(obj);
    delete obj;
}

void World::destroyAllObjects(ObjectSprite type)
{
    std::list<Object*>::iterator it = _objects.begin();
    while(it != _objects.end())
    {
        Object* obj = *it;
        if(obj->sprite() == type)
        {
            obj->removeFromWorld();
            _objects.erase(it++);
            delete obj;
        }
        else ++it;
    }
}

const std::list<Object*>& World::getObjectList() const { return _objects; }
Character* World::getCharacter(int playerId) const { return _character[playerId]; }

void World::setCrystalPos(b2Vec2 pos) { _crystalPos = pos; }
void World::activateCrystal()
{
    addObject(new Powerup(ObjectSprite::Crystal, _crystalPos));
    AudioManager::playSound(AudioManager::Crystal);
}

Game* World::game() const { return _game; }
b2World* World::physicWorld() { return &_physicWorld; }
const b2World* World::physicWorld() const { return &_physicWorld; }

void World::step()
{
    for(Object* o : _objects) o->step(Settings::frameTime);

    _physicWorld.Step(Settings::frameTime, 10, 8);

    checkWarp();
    for(Action actionFunc : _postStepActions) actionFunc();
    _postStepActions.clear();

    if(_game->levelType() == LevelType::Bonus) _timeLeft -= Settings::frameTime;
    if(_nextLevel || _timeLeft <= 0.f) _game->nextLevel();
}

void World::checkWarp()
{
    WarpChecker warpChecker(_size);
    b2AABB aabb;

    aabb.lowerBound = b2Vec2(-1.f, -1.f);
    aabb.upperBound = b2Vec2(1.f+_size.x, -1.f);
    _physicWorld.QueryAABB(&warpChecker, aabb);

    aabb.lowerBound = b2Vec2(-1.f, -1.f);
    aabb.upperBound = b2Vec2(-1.f, 1.f+_size.y);
    _physicWorld.QueryAABB(&warpChecker, aabb);

    aabb.lowerBound = b2Vec2(-1.f, 1.f+_size.y);
    aabb.upperBound = b2Vec2(1.f+_size.x, 1.f+_size.y);
    _physicWorld.QueryAABB(&warpChecker, aabb);

    aabb.lowerBound = b2Vec2(1.f+_size.x, -1.f);
    aabb.upperBound = b2Vec2(1.f+_size.x, 1.f+_size.y);
    _physicWorld.QueryAABB(&warpChecker, aabb);
}

void World::addPostStepAction(Action f) { _postStepActions.push_back(f); }
void World::nextLevel() { _nextLevel = true; }

World::~World()
{
    for(Object* obj : _objects) delete obj;
}
