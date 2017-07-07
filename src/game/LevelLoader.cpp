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
#include <tmxparser/TmxMap.h>
#include <tmxparser/TmxLayer.h>
#include <tmxparser/TmxTileLayer.h>
#include <tmxparser/TmxObjectGroup.h>
#include <tmxparser/TmxObject.h>
#include <tmxparser/TmxPolyline.h>

bool operator<(const b2Vec2& a, const b2Vec2& b)
{
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

LevelLoader::LevelLoader(const std::string& fileName, int nbPlayer)
{
    _fileName = "assets/level/"+fileName;
    _nbPlayer = nbPlayer;

    _sword = nullptr;
    _characterPhantom = nullptr;
}

const std::map<std::string, LevelType> LEVEL_TYPES = {{"classic", LevelType::Classic},
                                                      {"bonus", LevelType::Bonus},
                                                      {"boss", LevelType::Boss},
                                                      {"end", LevelType::End},
                                                      {"duel", LevelType::Duel}};

b2Vec2 pointMapPos(Tmx::Point pixelPos, int resol, Tmx::Point parentPos = Tmx::Point{0,0})
{
    b2Vec2 mapPos = b2Vec2(std::floor((parentPos.x+pixelPos.x)*resol/TILE_SIZE),
                           std::floor((parentPos.y+pixelPos.y)*resol/TILE_SIZE));
    mapPos *= (1.f/resol);

    return mapPos;
}

void LevelLoader::loadMap(World* w)
{
    w->reset();

    Tmx::Map map;
    map.ParseFile(_fileName);

    b2Vec2 size = b2Vec2(map.GetWidth(), map.GetHeight());
    int resol = TILE_SIZE/map.GetTileWidth();
    w->setSize((1.f/resol)*size);

    auto lvlTypeIt = LEVEL_TYPES.find(map.GetProperties().GetStringProperty("type"));
    if(lvlTypeIt != LEVEL_TYPES.end()) _lvlType = lvlTypeIt->second;
    else _lvlType = LevelType::Classic;

    if(_lvlType == LevelType::Bonus)
        w->setTimeLeft(map.GetProperties().GetIntProperty("timeLimit", 60));

    for(Tmx::TileLayer* layer : map.GetTileLayers())
    {
        if(layer->GetName() == "background")
        {
            unsigned bgId = layer->GetTileId(0,0);
            unsigned bgSize = 1;
            while(layer->GetTileId(bgSize*resol,0) != bgId) bgSize++;
            w->setBackgroundInfo(std::make_pair(bgId, bgSize));
        }
        else if(layer->GetName() == "map")
        {
            for(unsigned y = 0 ; y < size.y ; y++)
            {
                for(unsigned x = 0 ; x < size.x ; x++)
                {
                    if(layer->GetTileTilesetIndex(x,y) == -1) continue; // On passe les cases vides
                    ObjectSprite objType = static_cast<ObjectSprite>(layer->GetTileId(x,y));

                    b2Vec2 pos = (1.f/resol)*b2Vec2(x,y);
                    if(objType == ObjectSprite::Crystal) w->setCrystalPos(pos);
                    else if(objType == ObjectSprite::BlackCrystal) _blackCrystalPos = pos;

                    Object* obj = createObject(objType, pos);
                    if(!obj) continue;

                    w->addObject(obj);
                }
            }
        }
    }

    for(Tmx::ObjectGroup* objLayer : map.GetObjectGroups())
    {
        if(objLayer->GetName() == "paths")
        {
            for(Tmx::Object* pathObj : objLayer->GetObjects())
            {
                const Tmx::Polyline* pathLine = pathObj->GetPolyline();
                if(!pathLine) continue;

                Tmx::Point objPos = Tmx::Point{float(pathObj->GetX()), float(pathObj->GetY())};
                b2Vec2 originPoint = pointMapPos(objPos, resol);

                Object* obj = _objectsNeedingPath[originPoint];
                if(!obj) continue;

                Path* path;
                if(obj->sprite() == ObjectSprite::PhantomKiller) path = new QuadraticPath;
                else path = new LinearPath;

                for(int p = 0 ; p < pathLine->GetNumPoints() ; p++)
                {
                    path->addPoint(pointMapPos(pathLine->GetPoint(p), resol, objPos));
                }

                obj->setPath(path);
            }
        }
        else if(objLayer->GetName() == "teleporters")
        {
            for(Tmx::Object* tpObj : objLayer->GetObjects())
            {
                const Tmx::Polyline* pathLine = tpObj->GetPolyline();
                if(!pathLine) continue;

                Tmx::Point objPos = Tmx::Point{float(tpObj->GetX()), float(tpObj->GetY())};
                b2Vec2 originPoint = pointMapPos(objPos, resol);

                Teleporter* teleporter = _teleporters[originPoint];
                if(!teleporter) continue;

                b2Vec2 destination = pointMapPos(pathLine->GetPoint(1), resol, objPos);
                teleporter->setDestination(destination);
            }
        }
        else if(objLayer->GetName() == "switches")
        {
            for(Tmx::Object* linkObj : objLayer->GetObjects())
            {
                const Tmx::Polyline* linkLine = linkObj->GetPolyline();
                if(!linkLine) continue;

                Tmx::Point objPos = Tmx::Point{float(linkObj->GetX()), float(linkObj->GetY())};
                b2Vec2 originPoint = pointMapPos(objPos, resol);

                Switch* sw = _switches[originPoint];
                if(!sw) continue;

                for(int p = 1 ; p < linkLine->GetNumPoints() ; p++)
                {
                    b2Vec2 linkedPos = pointMapPos(linkLine->GetPoint(p), resol, objPos);
                    Object* linkedObj = _switchableObjects[linkedPos];
                    if(!linkedObj) continue;

                    sw->addLinkedObject(linkedObj);
                }
            }
        }
    }

    for(Boss* boss : _bosses) boss->setSword(_sword);

    if(_characterPhantom) _characterPhantom->setBlackCrystalPos(_blackCrystalPos);
}

LevelType LevelLoader::levelType() { return _lvlType; }
int LevelLoader::nbBoss() { return _bosses.size(); }

Object* LevelLoader::createObject(ObjectSprite type, b2Vec2 pos)
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
            _objectsNeedingPath[pos] = phantom;
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
            return new Wall(type, pos);
        case ObjectSprite::Door:
        {
            Wall* door = new Wall(type, pos);
            _switchableObjects[pos] = door;
            return door;
        }
        case ObjectSprite::Teleporter:
        {
            Teleporter* tp = new Teleporter(type, pos);
            _teleporters[pos] = tp;
            return tp;
        }
        case ObjectSprite::SwitchOn:
        case ObjectSprite::SwitchOff:
        {
            Switch* s = new Switch(type, pos);
            _switches[pos] = s;
            _switchableObjects[pos] = s;
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
