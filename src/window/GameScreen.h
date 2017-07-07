#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
#include "game/Game.h"
#include "game/views/Background.h"
#include "game/views/SpriteView.h"
#include "game/views/Foreground.h"
#include "game/views/LightComposer.h"
#include "game/views/Border.h"
#ifdef DEBUG
#  include "game/views/PhysicsDebugDraw.h"
#endif
namespace sf { class Lock; }

class GameScreen : public Screen
{
public:
    GameScreen(int nbPlayer, int levelListId, float speedFactor, Window*);
    ~GameScreen() = default;
    sf::Vector2u wantedSize() const override;
    void step() override;
    void prepareDraw() override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void updateSize() override;

private:
    void updatePlayerInputs(b2Vec2* inputs);

    Game _game;
    sf::Vector2f _topLeftOffset;
    Background _background;
    LightComposer _bgShadows;
    SpriteView _objectView;
    LightComposer _objShadows;
    SpriteView _wallsView;
    LightComposer _wallShadows;
    Foreground _foreground;
    Border _border;
#ifdef DEBUG
    PhysicsDebugDraw _physicsDebugDraw;
#endif
};

#endif // GAMESCREEN_H
