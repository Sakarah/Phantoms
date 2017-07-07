#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <fstream>
#include "common.h"
class World;
class Background;
class Object;
class Teleporter;
class Switch;
class Powerup;
class Boss;
class CharacterPhantom;

class LevelLoaderOld
{
public:
    LevelLoaderOld(std::string fileName, int nbPlayer);
    ~LevelLoaderOld() = default;
    void loadMap(World*);
    LevelType levelType();
    int nbBoss();
private:
    Object* createObject(ObjectSprite type, b2Vec2 pos);

    std::ifstream _fileStream;
    int _nbPlayer;
    LevelType _lvlType;
    std::vector<Object*> _objectsNeedingPath;
    std::vector<Teleporter*> _teleporters;
    std::vector<Object*> _switchableObjects;
    std::vector<Switch*> _switches;
    Powerup* _sword;
    std::vector<Boss*> _bosses;
    CharacterPhantom* _characterPhantom;
    b2Vec2 _blackCrystalPos;
};

#endif // MAPLOADER_H
