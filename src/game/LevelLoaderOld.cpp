#include "LevelLoader.h"
#include "World.h"
#include "objects/Object.h"
#include "objects/Phantom.h"
#include "objects/Character.h"
#include "objects/CharacterPhantom.h"
#include "objects/Wall.h"
#include "objects/Powerup.h"
#include "objects/Teleporter.h"
#include "objects/Switch.h"
#include "objects/Boss.h"
#include "paths/LinearPath.h"
#include "paths/QuadraticPath.h"

LevelLoaderOld::LevelLoaderOld(std::string fileName, int nbPlayer)
{
    std::string lvlName = "level/"+fileName;
    _fileStream.open(lvlName);
    _nbPlayer = nbPlayer;

    _sword = nullptr;
    _characterPhantom = nullptr;
}

void LevelLoaderOld::loadMap(World* w)
{
    w->reset();

    char levelType;
    _fileStream >> levelType;
    _lvlType = static_cast<LevelType>(levelType);

    b2Vec2 size;
    int resol;
    _fileStream >> size.x >> size.y >> resol;
    w->setSize(size);

    int bgId;
    int bgSize;
    _fileStream >> bgId >> bgSize;
    w->setBackgroundInfo(std::make_pair(bgId, bgSize));

    for(unsigned y = 0 ; y < size.y*resol ; y++)
    {
        for(unsigned x = 0 ; x < size.x*resol ; x++)
        {
            int t;
            _fileStream >> t;
            ObjectSprite objType = static_cast<ObjectSprite>(t);

            b2Vec2 pos = (1.f/resol)*b2Vec2(x,y);
            if(objType == ObjectSprite::Crystal) w->setCrystalPos(pos);
            else if(objType == ObjectSprite::BlackCrystal) _blackCrystalPos = pos;

            Object* obj = createObject(objType, pos);
            if(!obj) continue;

            w->addObject(obj);
            if(obj->flags() & SwitchableFlag) _switchableObjects.push_back(obj);
        }
    }

    for(Object* obj : _objectsNeedingPath)
    {
        Path* path;
        if(obj->sprite() == ObjectSprite::PhantomKiller) path = new QuadraticPath;
        else path = new LinearPath;

        obj->setPath(path);

        int nbPoints;
        _fileStream >> nbPoints;

        for(int p = 0 ; p < nbPoints ; p++)
        {
            b2Vec2 point;
            _fileStream >> point.x >> point.y;
            path->addPoint(point);
        }
    }

    for(Teleporter* tp : _teleporters)
    {
        b2Vec2 tpDest;
        _fileStream >> tpDest.x >> tpDest.y;

        tp->setDestination(tpDest);
    }

    for(Switch* sw : _switches)
    {
        int nbLinkedObj;
        _fileStream >> nbLinkedObj;

        for(int i = 0 ; i < nbLinkedObj ; i++)
        {
            int linkedObjId;
            _fileStream >> linkedObjId;

            sw->addLinkedObject(_switchableObjects[linkedObjId]);
        }
    }

    for(Boss* boss : _bosses) boss->setSword(_sword);

    if(_characterPhantom) _characterPhantom->setBlackCrystalPos(_blackCrystalPos);
}

LevelType LevelLoaderOld::levelType() { return _lvlType; }
int LevelLoaderOld::nbBoss() { return _bosses.size(); }

Object* LevelLoaderOld::createObject(ObjectSprite type, b2Vec2 pos)
{
    switch(type)
    {
        case ObjectSprite::Phantom:
        case ObjectSprite::PhantomExplosive:
        case ObjectSprite::PhantomFast:
            return new Phantom(type, pos);
        case ObjectSprite::PhantomPatroller:
        case ObjectSprite::PhantomKiller:
        {
            Phantom* phantom = new Phantom(type, pos);
            _objectsNeedingPath.push_back(phantom);
            return phantom;
        }
        case ObjectSprite::Character4:
            if(_nbPlayer < 4) return nullptr;
        case ObjectSprite::Character3:
            if(_nbPlayer < 3) return nullptr;
        case ObjectSprite::Character2:
            if(_nbPlayer < 2) return nullptr;
        case ObjectSprite::Character1:
            return new Character(type, pos);
        case ObjectSprite::PhantomPlayer:
            _characterPhantom = new CharacterPhantom(type, pos);
            return _characterPhantom;
        case ObjectSprite::Crystal:
            if(_lvlType != LevelType::Bonus) return nullptr;
        case ObjectSprite::Coin:
        case ObjectSprite::Coin2:
        case ObjectSprite::Life:
        case ObjectSprite::Key:
        case ObjectSprite::Power:
        case ObjectSprite::BlackCoin:
        case ObjectSprite::Bomb:
        case ObjectSprite::Chest:
            return new Powerup(type, pos);
        case ObjectSprite::Wall:
        case ObjectSprite::WallAlt:
        case ObjectSprite::Lock:
        case ObjectSprite::Door:
            return new Wall(type, pos);
        case ObjectSprite::Teleporter:
        {
            Teleporter* tp = new Teleporter(type, pos);
            _teleporters.push_back(tp);
            return tp;
        }
        case ObjectSprite::SwitchOn:
        case ObjectSprite::SwitchOff:
        {
            Switch* s = new Switch(type, pos);
            _switches.push_back(s);
            return s;
        }
        case ObjectSprite::Sword:
            _sword = new Powerup(type, pos);
            return _sword;
        case ObjectSprite::Boss:
        {
            Boss* boss = new Boss(type, pos);
            _bosses.push_back(boss);
            return boss;
        }
        default:
            return nullptr;
    }
}
