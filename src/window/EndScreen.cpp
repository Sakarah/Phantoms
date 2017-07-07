#include "EndScreen.h"
#include "Window.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "../resources/AudioManager.h"
#include "../resources/AssetManager.h"
#include "../resources/ReplayRecorder.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

EndScreen::EndScreen(GameEnd end, int score, Window* win) : Screen(win)
{
    _endType = end;
    _score = score;
    if(_endType == GameEnd::GameOver || _endType == GameEnd::DuelVictoryPhantom) AudioManager::setMusic(AudioManager::GameOver, false);
    else AudioManager::setMusic(AudioManager::Victory, false);
}

void EndScreen::handleEvent(sf::Event& ev)
{
    if(ev.type == sf::Event::KeyPressed)
    {
        if(ev.key.code == sf::Keyboard::Escape || ev.key.code == sf::Keyboard::Space || ev.key.code == sf::Keyboard::Return)
        {
            if(ReplayRecorder::replayMode() == ReplayRecorder::Replay) _window->setScreen(new GameScreen(0, 0, 0, _window));
            else _window->setScreen(new MenuScreen(_window));
        }
    }
}

void EndScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    switch (_endType)
    {
        case GameEnd::GameOver:
        {
            target.clear(sf::Color(0,0,0));
            drawCenteredText(wtr("Game Over"), AssetManager::getFont(AssetManager::GameOver), 64, sf::Color(255,255,255), 100, target, states);
            sf::String scoreStr = wfmt(tr("Score: %d"), _score);
            drawCenteredText(scoreStr, AssetManager::getFont(AssetManager::GameOver), 40, sf::Color(255,255,0), 250, target, states);
            break;
        }
        case GameEnd::Victory:
        {
            target.clear(sf::Color(0,0,0));
            drawCenteredText(wtr("You have won!"), AssetManager::getFont(AssetManager::Victory), 64, sf::Color(255,255,255), 100, target, states);
            sf::String scoreStr = wfmt(tr("Score: %d"), _score);
            drawCenteredText(scoreStr, AssetManager::getFont(AssetManager::GameOver), 40, sf::Color(255,255,0), 250, target, states);
            break;
        }
        case GameEnd::DuelVictoryPlayer:
        {
            target.clear(sf::Color(255,255,0));
            drawCenteredText(wtr("Victory:"), AssetManager::getFont(AssetManager::Victory), 40, sf::Color(0,0,0), 100, target, states);
            drawCenteredText(wtr("Player"), AssetManager::getFont(AssetManager::Victory), 100, sf::Color(0,0,0), 150, target, states);
            break;
        }
        case GameEnd::DuelVictoryPhantom:
        {
            target.clear(sf::Color(0,255,255));
            drawCenteredText(wtr("Victory:"), AssetManager::getFont(AssetManager::GameOver), 40, sf::Color(0,0,0), 100, target, states);
            drawCenteredText(wtr("Phantom"), AssetManager::getFont(AssetManager::GameOver), 100, sf::Color(0,0,0), 150, target, states);
            break;
        }
        case GameEnd::NotEnded:
            break;
    }
}

void EndScreen::drawCenteredText(sf::String text, sf::Font& font, int size, sf::Color color, int vPos,
                                 sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Vector2f winSize = target.getView().getSize();
    sf::Text renderedText(text, font, size);
    renderedText.setFillColor(color);
    renderedText.setPosition((winSize.x-renderedText.getLocalBounds().width)/2, winSize.y/2 - 240 + vPos);
    target.draw(renderedText, states);
}
