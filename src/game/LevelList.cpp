#include "LevelList.h"
#include <fstream>

std::vector<LevelList> LevelList::_levelLists;

LevelList::LevelList(const std::string& fileName)
{
    std::ifstream fileStream;
    fileStream.open("assets/level/"+fileName);

    fileStream >> name;
    fileStream >> playerMinMax.first >> playerMinMax.second;

    std::string levelName;
    fileStream >> levelName;
    while(!levelName.empty())
    {
        levelNames.push_back(levelName);
        levelName.clear();
        fileStream >> levelName;
    }
}

void LevelList::loadLists()
{
    std::ifstream fileStream;
    fileStream.open("assets/level/levelLists.cfg");

    std::string listName;
    fileStream >> listName;
    while(!listName.empty())
    {
        _levelLists.push_back(LevelList(listName));
        listName.clear();
        fileStream >> listName;
    }
}

int LevelList::nbLevelList() { return _levelLists.size(); }
const LevelList* LevelList::getLevelList(int id) { return &_levelLists[id]; }
