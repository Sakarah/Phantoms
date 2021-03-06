#include "Foreground.h"
#include "../Game.h"
#include "../../graphics.h"
#include "../../resources/AssetManager.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

Foreground::Foreground(const Game* game)
{
    _game = game;
}

void Foreground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Vector2f winSize = target.getView().getSize();

    int nbLives = _game->nbLives();
    sf::VertexArray lifeVertices(sf::Quads, nbLives*4);
    for(int i = 0 ; i < nbLives ; i++)
    {
        sf::IntRect spriteTexRect = rectForTilesetId(static_cast<int>(ObjectSprite::Life));
        genSpriteVertices(&lifeVertices[i*4], sf::Vector2i(i*32, 0), spriteTexRect);
    }
    states.texture = AssetManager::getTileset(AssetManager::Sprite);
    target.draw(lifeVertices, states);

    sf::String scoreText = wfmt(tr("Score: %d"), _game->score());
    sf::Text score(scoreText, AssetManager::getFont(AssetManager::Gui), 24);
    score.setFillColor(sf::Color(250, 200, 0));
    score.setPosition(winSize.x - 128, 0);
    target.draw(score, states);

    if(_game->levelType() == LevelType::Classic)
    {
        sf::String nextLevelText;
        if(_game->isLevelCleared()) nextLevelText = tr("Next level available");
        else
        {
            nextLevelText = wnftr("Next level after %d more coin", "Next level after %d more coins", _game->coinsLeft());
        }
        sf::Text nextLevel(nextLevelText, AssetManager::getFont(AssetManager::Gui), 24);
        nextLevel.setFillColor(_game->isLevelCleared() ? sf::Color(0,255,255) : sf::Color(0, 255, 0));
        nextLevel.setPosition(4, winSize.y - 32);
        target.draw(nextLevel, states);
    }
    else if(_game->levelType() == LevelType::Boss)
    {
        sf::Text bossText(_game->isLevelCleared() ? wtr("Boss defeated") : wtr("BOSS !"), AssetManager::getFont(AssetManager::Gui), 24);
        bossText.setFillColor(_game->isLevelCleared() ? sf::Color(0,255,255) : sf::Color(255, 0, 0));
        bossText.setPosition(4, winSize.y - 32);
        target.draw(bossText, states);
    }
    else if(_game->levelType() == LevelType::Bonus)
    {
        sf::Text timeText(wfmt(tr("Time left: %ds"), int(_game->world()->timeLeft())),
                          AssetManager::getFont(AssetManager::Gui), 24);
        timeText.setFillColor(sf::Color(255,0,255));
        timeText.setPosition(4, winSize.y - 32);
        target.draw(timeText, states);
    }
}
