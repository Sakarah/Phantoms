#ifndef FRAME_H
#define FRAME_H

#include "../../common.h"
#include "LightSource.h"
#include <SFML/System/Mutex.hpp>
#include <SFML/Graphics/Color.hpp>
class Game;
class b2World;

struct ObjectInfos
{
    sf::Vector2i pos;
    ObjectSprite sprite;
    uint16 flags;
};

struct GameInfos
{
    LevelType levelType;
    int nbLives;
    int score;
    int coinsLeft;
    int timeLeft;
    bool levelCleared;
};

struct Frame
{
    void update(const Game&);

    enum FrameState
    {
        ReadyToUpdate,
        ReadyToDraw
    };

    sf::Vector2u size;
    std::pair<int,int> backgroundInfo;
    std::vector<ObjectInfos> objectsInfos;
    std::vector<LightSource> lightSources;
    sf::Color ambientLight;
    sf::Color ambientObjectLight;
    GameInfos gameInfos;

    b2Vec2 playerInputs[4];

    mutable sf::Mutex mutex;
    FrameState state;
};

#endif // FRAME_H
