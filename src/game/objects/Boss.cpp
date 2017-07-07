#include "Boss.h"
#include "Phantom.h"
#include "Powerup.h"
#include "../World.h"
#include "../Game.h"
#include "../gameplay.h"
#include "../../Random.h"
#include "../../resources/AudioManager.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

Boss::Boss(ObjectSprite sprite, b2Vec2 pos) : Object(sprite, pos)
{
    _flags = PhantomFlag | BigSpriteFlag;
    _nbLives = BOSS_LIVES;
}

void Boss::setSword(Powerup* sword) { _sword = sword; }

void Boss::addToWorld(World* world)
{
    _world = world;
    _timeLeftBeforeSpawn = BOSS_SPAWN_TIME/_world->speedFactor();
    b2World* physicWorld = world->physicWorld();

    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.fixedRotation = true;
    bodyDef.position = _startPos;
    bodyDef.type = b2_staticBody;
    _physicBody = physicWorld->CreateBody(&bodyDef);

    b2FixtureDef fixDef;
    b2CircleShape circleShape;
    circleShape.m_p = b2Vec2(1, 1);
    circleShape.m_radius = 1;
    fixDef.shape = &circleShape;
    fixDef.isSensor = true;
    b2Fixture* fix = _physicBody->CreateFixture(&fixDef);

    b2Filter filter;
    filter.categoryBits = PhantomFlag;
    filter.maskBits = CharacterFlag;
    fix->SetFilterData(filter);
}

void Boss::step(float time)
{
    _timeLeftBeforeSpawn -= time;
    if(_timeLeftBeforeSpawn < 0)
    {
        ObjectSprite phantomType = Random::bernoulliTest() ? ObjectSprite::Phantom : ObjectSprite::PhantomExplosive;
        Phantom* spawningPhantom = new Phantom(phantomType, _startPos+b2Vec2(0.5,0.5));
        _world->addPostStepAction([this,spawningPhantom]{_world->addObject(spawningPhantom);});

        _timeLeftBeforeSpawn = BOSS_SPAWN_TIME/_world->speedFactor();
    }

    _sprite = _sword->isActive() ? ObjectSprite::Boss : ObjectSprite::VulnerableBoss;
}

void Boss::contactWith(Object* other)
{
    if(other->flags() & CharacterFlag)
    {
        if(_sword->isActive())
        {
            _world->addPostStepAction([other]{other->jumpToStartPos();});
            _world->game()->loseLife();
        }
        else
        {
            _nbLives--;
            _world->game()->addScore(10);
            _world->addPostStepAction([this]{_sword->jumpToRandomPos();});
            _world->addPostStepAction([this]{_sword->setActive(true);});
            _world->addPostStepAction([other]{other->jumpToStartPos();});
            AudioManager::playSound(AudioManager::SwordHit);

            if(_nbLives == 0)
            {
                _world->game()->bossKilled();
                if(_world->game()->isLevelCleared())
                {
                     _world->addPostStepAction([this]{_world->destroyObject(_sword);});
                     _world->addPostStepAction([this]{_world->activateCrystal();});
                }
                _world->addPostStepAction([this]{_world->destroyObject(this);});
            }
        }
    }
}
