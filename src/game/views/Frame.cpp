#include "Frame.h"
#include "../Game.h"
#include "../objects/Object.h"

void Frame::update(const Game& game)
{
    b2Vec2 frameSize = TILE_SIZE*game.world()->size();
    size = sf::Vector2u(frameSize.x, frameSize.y);
    backgroundInfo = game.world()->backgroundInfo();

    objectsInfos.clear();
    lightSources.clear();
    for(Object* obj : game.world()->getObjectList())
    {
        if(!obj->isActive()) continue;
        if(!obj->currentPos().IsValid()) continue;

        ObjectInfos objInfos;
        objInfos.pos = obj->currentPixelPos();
        objInfos.sprite = obj->sprite();
        objInfos.flags = obj->flags();
        objectsInfos.push_back(objInfos);

        if(obj->lightRadius() != 0)
        {
            lightSources.push_back(LightSource(obj->currentPos(), obj->lightRadius(), obj->lightColor()));
            lightSources.back().computeLight(game.world()->physicWorld());
        }
    }

    ambientLight = sf::Color(100,100,100);
    ambientObjectLight = sf::Color(100,100,100,100);

    gameInfos.levelType = game.levelType();
    gameInfos.nbLives = game.nbLives();
    gameInfos.score = game.score();
    gameInfos.coinsLeft = game.coinsLeft();
    gameInfos.timeLeft = game.world()->timeLeft();
    gameInfos.levelCleared = game.isLevelCleared();
}
