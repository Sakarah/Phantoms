#include "Character.h"
#include "Powerup.h"
#include "../Game.h"
#include "../gameplay.h"
#include "../../resources/AudioManager.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

Character::Character(ObjectSprite type, b2Vec2 pos) : Object(type, pos)
{
    _flags = CharacterFlag;
    _invincibilityTimeLeft = 0.f;
    _lightRadius = PLAYER_LIGHT_RADIUS;
    _lightColor = sf::Color::White;
}

void Character::addToWorld(World* world)
{
    _world = world;
    b2World* physicWorld = world->physicWorld();

    _velocity = PLAYER_SPEED*world->speedFactor();

    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.fixedRotation = true;
    bodyDef.position = _startPos;
    bodyDef.type = b2_dynamicBody;
    _physicBody = physicWorld->CreateBody(&bodyDef);

    b2FixtureDef fixDef;
    b2CircleShape circleShape;
    circleShape.m_p = b2Vec2(0.5, 0.5);
    circleShape.m_radius = 0.45;
    fixDef.shape = &circleShape;
    fixDef.friction = 0.f;
    b2Fixture* fix = _physicBody->CreateFixture(&fixDef);

    b2Filter filter;
    filter.categoryBits = CharacterFlag;
    filter.maskBits = PhantomFlag | ItemFlag | WallFlag;
    fix->SetFilterData(filter);
}

void Character::step(float time)
{
    if(_invincibilityTimeLeft != 0)
    {
        _invincibilityTimeLeft -= time;
        if(_invincibilityTimeLeft <= 0)
        {
            _invincibilityTimeLeft = 0;
            _flags &= AllFlags ^ SemiTransparentFlag;
        }
    }
}

void Character::contactWith(Object* other)
{
    switch(other->sprite())
    {
        case ObjectSprite::Phantom:
        case ObjectSprite::PhantomFast:
        case ObjectSprite::PhantomKiller:
        case ObjectSprite::PhantomPatroller:
        case ObjectSprite::PhantomPlayer:
            _world->addPostStepAction([other]{other->jumpToStartPos();});
            if(_invincibilityTimeLeft == 0)
            {
                _world->addPostStepAction([this]{jumpToStartPos();});
                _world->game()->loseLife();
                giveInvincibility();
            }
            break;
        case ObjectSprite::PhantomExplosive:
            _world->addPostStepAction([other]{other->world()->destroyObject(other);});
            if(_invincibilityTimeLeft == 0)
            {
                _world->addPostStepAction([this]{jumpToStartPos();});
                _world->game()->loseLife(2);
                giveInvincibility();
                AudioManager::playSound(AudioManager::Explosion);
            }
            break;
        case ObjectSprite::Coin:
            _world->game()->coinTaken();
            if(!_world->game()->isLevelCleared()) _world->addPostStepAction([other]{other->jumpToRandomPos();});
            else
            {
                _world->addPostStepAction([other]{other->world()->destroyObject(other);});
                if(_world->game()->levelType() != LevelType::Bonus) _world->addPostStepAction([this]{_world->activateCrystal();});
            }
            break;
        case ObjectSprite::Coin2:
            _world->game()->addScore(2);
            _world->addPostStepAction([other]{other->world()->destroyObject(other);});
            AudioManager::playSound(AudioManager::Gold);
            break;
        case ObjectSprite::Life:
            _world->addPostStepAction([other]{other->world()->destroyObject(other);});
            _world->game()->lifeBonus();
            break;
        case ObjectSprite::Key:
            _world->addPostStepAction([other]{other->world()->destroyObject(other);});
            _world->addPostStepAction([this]{_world->destroyAllObjects(ObjectSprite::Lock);});
            AudioManager::playSound(AudioManager::Switch);
            break;
        case ObjectSprite::Crystal:
            if(_world->game()->levelType() == LevelType::Duel) _world->game()->endGame(GameEnd::DuelVictoryPlayer);
            else _world->nextLevel();
            break;
        case ObjectSprite::Bomb:
            _world->addPostStepAction([this]{jumpToStartPos();});
            AudioManager::playSound(AudioManager::Explosion);
            break;
        case ObjectSprite::Power:
            for(Object* obj : _world->getObjectList())
            {
                if(obj->flags() & CoinFlag) _world->addPostStepAction([obj]{obj->jumpToRandomPos();});
            }
            _world->addPostStepAction([other]{other->jumpToRandomPos();});
            AudioManager::playSound(AudioManager::Power);
            break;
        case ObjectSprite::BlackCoin:
            _world->addPostStepAction([other]{other->jumpToRandomPos();});
            AudioManager::playSound(AudioManager::Power);
            break;
        case ObjectSprite::Sword:
            _world->addPostStepAction([other]{other->setActive(false);});
            AudioManager::playSound(AudioManager::SwordTaken);
            break;
        case ObjectSprite::Chest:
            _world->game()->addScore(50*_world->game()->nbLives()*_world->speedFactor());
            _world->game()->endGame(GameEnd::Victory);
            break;
        case ObjectSprite::Boss:
            giveInvincibility();
            break;
        default:
            break;
    }
}

void Character::giveInvincibility()
{
    _invincibilityTimeLeft = INVINCIBILITY_TIME/_world->speedFactor();
    _flags |= SemiTransparentFlag;
}
