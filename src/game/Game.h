#ifndef GAME_H
#define GAME_H

#include "World.h"
#include "LevelList.h"
#include "LevelLoader.h"

class Game
{
public:
    Game(int nbPlayer, int levelListId, float speedFactor);
    ~Game() = default;
    World* world();
    const World* world() const;

    int nbPlayer() const;
    float speedFactor() const;
    LevelType levelType() const;
    int nbLives() const;
    bool hasEnded() const;
    GameEnd endType() const;
    int score() const;
    int coinsLeft() const;
    bool isLevelCleared() const;

    void loadLevel();
    void moveCharacter(int id, b2Vec2 dir);
    void coinTaken();
    void bossKilled();
    void loseLife(int nb = 1);
    void lifeBonus();
    void addScore(int points);
    void nextLevel();
    void endGame(GameEnd type);

private:
    World _world;
    int _nbPlayer;
    const LevelList* _levelList;
    int _level;
    GameEnd _end;
    LevelType _lvlType;
    int _nbLife;
    int _score;
    int _coinsLeft;
    int _bossLeft;
};

#endif // GAME_H
