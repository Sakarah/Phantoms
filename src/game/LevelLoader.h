#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <map>
#include "common.h"
class World;
class Background;
class Object;
class Teleporter;
class Switch;
class Powerup;
class Boss;
class CharacterPhantom;

// Lexicographic order (x then y)
bool operator<(const b2Vec2&, const b2Vec2&);

class LevelLoader
{
public:
    LevelLoader(const std::string& fileName, int nbPlayer);
    ~LevelLoader() = default;
    void loadMap(World*);
    LevelType levelType();
    int nbBoss();
private:
    Object* createObject(ObjectSprite type, b2Vec2 pos);

    std::string _fileName;
    int _nbPlayer;
    LevelType _lvlType;
    std::map<b2Vec2, Object*> _objectsNeedingPath;
    std::map<b2Vec2, Teleporter*> _teleporters;
    std::map<b2Vec2, Object*> _switchableObjects;
    std::map<b2Vec2, Switch*> _switches;
    Powerup* _sword;
    std::vector<Boss*> _bosses;
    CharacterPhantom* _characterPhantom;
    b2Vec2 _blackCrystalPos;
};

#endif // MAPLOADER_H
