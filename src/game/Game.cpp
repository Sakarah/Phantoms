#include "Game.h"
#include "gameplay.h"
#include "objects/Character.h"
#include "../resources/AudioManager.h"
#include "../resources/ReplayRecorder.h"

Game::Game(int nbPlayer, int levelListId, float speedFactor) : _world(this)
{
    ReplayRecorder::logValue(nbPlayer);
    ReplayRecorder::logValue(levelListId);
    ReplayRecorder::logValue(speedFactor);

    _nbPlayer = nbPlayer;
    _levelList = LevelList::getLevelList(levelListId);
    _world.setSpeedFactor(speedFactor);
    _end = GameEnd::NotEnded;
    _nbLife = 3*nbPlayer;
    _score = 0;
    _level = 0;
}

World* Game::world() { return &_world; }
const World* Game::world() const { return &_world; }

int Game::nbPlayer() const { return _nbPlayer; }
LevelType Game::levelType() const { return _lvlType; }
int Game::nbLives() const { return _nbLife; }
bool Game::hasEnded() const { return _end != GameEnd::NotEnded; }
GameEnd Game::endType() const { return _end; }
int Game::score() const { return _score; }
int Game::coinsLeft() const { return _coinsLeft; }
bool Game::isLevelCleared() const
{
    if(_lvlType == LevelType::Classic) return _coinsLeft == 0;
    else if(_lvlType == LevelType::Boss) return _bossLeft == 0;
    else if(_lvlType == LevelType::Duel) return _score >= DUEL_MODE_PLAYER_OBJECTIVE;
    return true;
}

void Game::loadLevel()
{
    _coinsLeft = COINS_PER_LEVEL;

    LevelLoader loader(_levelList->levelNames[_level], _nbPlayer);
    loader.loadMap(&_world);
    _lvlType = loader.levelType();
    _bossLeft = loader.nbBoss();

    if(_lvlType == LevelType::Classic) AudioManager::setMusic(AudioManager::Level);
    else if(_lvlType == LevelType::Bonus) AudioManager::setMusic(AudioManager::Bonus);
    else if(_lvlType == LevelType::Boss) AudioManager::setMusic(AudioManager::Boss);
    else if(_lvlType == LevelType::Duel) AudioManager::setMusic(AudioManager::Duel);
    else AudioManager::setMusic(AudioManager::Silence);
}

void Game::moveCharacter(int id, b2Vec2 dir)
{
    Character* c = _world.getCharacter(id);
    if(c) c->move(dir);
}

void Game::coinTaken()
{
    _score++;
    if(_lvlType == LevelType::Duel) _score++;
    _coinsLeft--;
    AudioManager::playSound(AudioManager::Gold);
}
void Game::bossKilled()
{
    _bossLeft--;
    AudioManager::playSound(AudioManager::BossDie);
}

void Game::loseLife(int nb)
{
    _nbLife -= nb;
    if(_nbLife <= 0)
    {
        _nbLife = 0;
        endGame(_lvlType == LevelType::Duel ? GameEnd::DuelVictoryPhantom : GameEnd::GameOver);
    }
    AudioManager::playSound(AudioManager::Touched);
}
void Game::lifeBonus()
{
    _nbLife += _nbPlayer;
    AudioManager::playSound(AudioManager::Life);
}
void Game::addScore(int points) { _score += points; }

void Game::nextLevel()
{
    _nbLife++;
    _score += 10;
    _level++;
    loadLevel();
    AudioManager::playSound(AudioManager::Teleport);
}

void Game::endGame(GameEnd type) { _end = type; }
