#ifndef LEVELLIST_H
#define LEVELLIST_H

#include "common.h"

struct LevelList
{
    ~LevelList() = default;

    std::string name;
    std::pair<int,int> playerMinMax;
    std::vector<std::string> levelNames;

    static void loadLists();
    static int nbLevelList();
    static const LevelList* getLevelList(int id);

private:
    LevelList(std::string fileName);
    static std::vector<LevelList> _levelLists;
};

#endif // LEVELLIST_H
