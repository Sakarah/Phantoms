#include "GameScreen.h"
#include "Window.h"
#include "EndScreen.h"
#include "../resources/Settings.h"
#include "../resources/ReplayRecorder.h"
#include "../game/objects/Object.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Lock.hpp>

GameScreen::GameScreen(int nbPlayer, int levelListId, float speedFactor, Window* w) :
    Screen(w),
    _game(nbPlayer, levelListId, speedFactor),
    _objectView(_game.world()),
    _wallsView(_game.world()),
    _foreground(&_game)
{
    _game.loadLevel();
#ifdef DEBUG
    _physicsDebugDraw.setupDebugDraw(_game.world());
#endif

    _objectView.setSpriteFilter(CharacterFlag | PhantomFlag | ItemFlag | CoinFlag);
    _wallsView.setSpriteFilter(WallFlag);
    _bgShadows.setView(&_background);
    _bgShadows.setFlags(Settings::lightQuality >= 1 ? LightComposer::BlurWholeShadows : LightComposer::None);
    _objShadows.setView(&_objectView);
    _objShadows.setFlags(Settings::lightQuality >= 1 ? LightComposer::BlurWholeShadows : LightComposer::None);
    _wallShadows.setView(&_wallsView);
    _wallShadows.setFlags(LightComposer::IgnoreWalls);
    updateSize();
}

sf::Vector2u GameScreen::wantedSize() const
{
    b2Vec2 winSize = TILE_SIZE*_game.world()->size();
    return sf::Vector2u(winSize.x, winSize.y);
}

const b2Vec2 DIRECTION[4] = { b2Vec2(-1,0), b2Vec2(1,0), b2Vec2(0,-1), b2Vec2(0,1) };

void GameScreen::step()
{
    for(int player = 0 ; player < _game.nbPlayer() ; player++)
    {
        _game.moveCharacter(player, b2Vec2(0,0));
        for(int dir = 0 ; dir < 4 ; dir++)
        {
            bool keyPressed = sf::Keyboard::isKeyPressed(Settings::controls[player].keys[dir]);
            ReplayRecorder::logBool(keyPressed);
            if(keyPressed) _game.moveCharacter(player, DIRECTION[dir]);
        }
    }

    b2Vec2 oldWorldSize = _game.world()->size();

    _game.world()->step();

    if(!(_game.world()->size() == oldWorldSize))
    {
        _window->updateSize();
        updateSize();
    }
    if(_game.hasEnded()) _window->setScreen(new EndScreen(_game.endType(), _game.score(), _window));
}

void GameScreen::prepareDraw()
{
    sf::Vector2u frameSize = toPixelSize(_game.world()->size());
    _background.setBackground(frameSize, _game.world()->backgroundInfo());
    _border.setGameSize(frameSize);

    std::vector<LightSource> lightSources;
    for(Object* obj : _game.world()->getObjectList())
    {
        if(!obj->isActive()) continue;
        if(obj->lightRadius() != 0)
        {
            lightSources.push_back(LightSource(obj->currentPos(), obj->lightRadius(), obj->lightColor()));
            lightSources.back().computeLight(_game.world()->physicWorld());
        }
    }

    const sf::Color ambientLight(100,100,100);
    const sf::Color ambientObjectLight(100,100,100,100);

    _bgShadows.renderLights(frameSize, lightSources, ambientLight);
    _objShadows.renderLights(frameSize, lightSources, ambientObjectLight);
    _wallShadows.renderLights(frameSize, lightSources, ambientLight);
}

void GameScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform.translate(_topLeftOffset);

    target.draw(_bgShadows, states);
    target.draw(_objShadows, states);
    target.draw(_wallShadows, states);
#ifdef DEBUG
    target.draw(_physicsDebugDraw, states);
#endif
    target.draw(_border, states);

    states.transform.translate(-_topLeftOffset);
    target.draw(_foreground, states);
}

void GameScreen::updateSize()
{
    sf::Vector2f winSize = _window->getView().getSize();
    _topLeftOffset = sf::Vector2f(int((winSize.x-_game.world()->size().x*TILE_SIZE)/2), int((winSize.y-_game.world()->size().y*TILE_SIZE)/2));
    _border.setWindowSize(winSize);
}
