#include "CharacterPhantom.h"
#include "Powerup.h"
#include "../World.h"
#include "../Game.h"
#include "../gameplay.h"
#include "../../resources/AudioManager.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

CharacterPhantom::CharacterPhantom(ObjectSprite sprite, b2Vec2 pos) : Character(sprite, pos)
{
    _flags |= PhantomFlag;
    _lightColor = sf::Color(120,255,255);
}

void CharacterPhantom::setBlackCrystalPos(b2Vec2 pos) { _blackCrystalPos = pos; }

void CharacterPhantom::addToWorld(World* world)
{
    _world = world;
    b2World* physicWorld = world->physicWorld();

    _velocity = PLAYER_PHANTOM_SPEED*_world->speedFactor();

    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.fixedRotation = true;
    bodyDef.position = _startPos;
    bodyDef.type = b2_dynamicBody;
    _physicBody = physicWorld->CreateBody(&bodyDef);

    b2FixtureDef fixDef;
    b2CircleShape circleShape;
    circleShape.m_p = b2Vec2(0.5, 0.5);
    circleShape.m_radius = 0.49;
    fixDef.shape = &circleShape;
    fixDef.friction = 0.f;
    b2Fixture* fix = _physicBody->CreateFixture(&fixDef);

    b2Filter filter;
    filter.categoryBits = CharacterFlag | PhantomFlag;
    filter.maskBits = CharacterFlag | ItemFlag | WallFlag;
    fix->SetFilterData(filter);
}

void CharacterPhantom::contactWith(Object* other)
{
    switch(other->sprite())
    {
        case ObjectSprite::BlackCoin:
            _world->game()->addScore(-1);
            AudioManager::playSound(AudioManager::Slowed);
            if(_world->game()->score() > DUEL_MODE_PHANTOM_OBJECTIVE) _world->addPostStepAction([other]{other->jumpToRandomPos();});
            else
            {
                _world->addPostStepAction([other]{other->world()->destroyObject(other);});
                _world->addPostStepAction([this]{_world->addObject(new Powerup(ObjectSprite::BlackCrystal, _blackCrystalPos));});
                AudioManager::playSound(AudioManager::Crystal);
            }
            break;
        case ObjectSprite::Power:
            for(Object* obj : _world->getObjectList())
            {
                if(obj->flags() & CoinFlag) _world->addPostStepAction([obj]{obj->jumpToRandomPos();});
            }
            _world->addPostStepAction([other]{other->jumpToRandomPos();});
            AudioManager::playSound(AudioManager::Power);
            break;
        case ObjectSprite::Coin:
            _world->addPostStepAction([other]{other->jumpToRandomPos();});
            AudioManager::playSound(AudioManager::Power);
            break;
        case ObjectSprite::BlackCrystal:
            _world->game()->endGame(GameEnd::DuelVictoryPhantom);
            break;
        default:
            break;
    }
}
