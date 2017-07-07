#include "HelpScreen.h"
#include "../graphics.h"
#include "../resources/AssetManager.h"
#include "Window.h"
#include "MenuScreen.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

HelpScreen::HelpScreen(Window* w) : Screen(w)
{
    _currentPage = 0;
    updateSize();
}

void HelpScreen::handleEvent(sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Escape) _window->setScreen(new MenuScreen(_window));
        else if(event.key.code == sf::Keyboard::Left && _currentPage > 0) _currentPage--;
        else if(event.key.code == sf::Keyboard::Right && _currentPage < 5) _currentPage++;
    }
}

void HelpScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = AssetManager::getTileset(AssetManager::HelpSettings);
    target.draw(_bgVertices, states);

    states.transform.translate(_topLeftOffset);
    switch(_currentPage)
    {
        case 0:
        {
            writeCenteredText(wtr("Welcome in Phantom's help"), 32, 100, target, states);

            writeCenteredText(wtr("Use arrow keys to navigate between pages"), 16, 200, target, states);
            writeCenteredText(wtr("Type <Esc> to return to menu"), 16, 220, target, states);

            break;
        }
        case 1:
        {
            writeCenteredText(wtr("In this game you must"), 32, 68, target, states);
            writeCenteredText(wtr("catch the maximum of coins"), 32, 100, target, states);
            writeCenteredText(wtr("with the smiling character(s)"), 32, 132, target, states);

            sf::VertexArray vertices(sf::Quads);
            vertices.resize(3*4);
            genSpriteVertices(&vertices[0], sf::Vector2i(208, 208), rectForTilesetId(2));
            genSpriteVertices(&vertices[4], sf::Vector2i(272, 208), sf::IntRect(sf::Vector2i(0,64), sf::Vector2i(96,32)));
            genSpriteVertices(&vertices[8], sf::Vector2i(400, 208), rectForTilesetId(32));
            target.draw(vertices, states);

            writeCenteredText(wtr("Each coin gives you 1 point"), 24, 300, target, states);

            break;
        }
        case 2:
        {
            writeCenteredText(wtr("At the same time you must"), 32, 68, target, states);
            writeCenteredText(wtr("absolutely avoid beeing"), 32, 100, target, states);
            writeCenteredText(wtr("touched by a ghost"), 32, 132, target, states);

            sf::VertexArray vertices(sf::Quads);
            vertices.resize(3*4);
            genSpriteVertices(&vertices[0], sf::Vector2i(208, 208), rectForTilesetId(2));
            genSpriteVertices(&vertices[4], sf::Vector2i(272, 208), sf::IntRect(sf::Vector2i(0,96), sf::Vector2i(96,32)));
            genSpriteVertices(&vertices[8], sf::Vector2i(400, 208), rectForTilesetId(19));
            target.draw(vertices, states);

            writeCenteredText(wtr("If it happens, you will lose 1 life"), 24, 300, target, states);
            writeCenteredText(wtr("Be careful : The ghosts are not identical and may have special skills"), 16, 350, target, states);

            break;
        }
        case 3:
        {
            writeCenteredText(wtr("Once you have gathered enough coins"), 32, 68, target, states);
            writeCenteredText(wtr("a diamond-shaped teleporter will appear"), 32, 100, target, states);
            writeCenteredText(wtr("to open you the next level"), 32, 132, target, states);

            sf::VertexArray vertices(sf::Quads);
            vertices.resize(3*4);
            genSpriteVertices(&vertices[0], sf::Vector2i(208, 208), rectForTilesetId(2));
            genSpriteVertices(&vertices[4], sf::Vector2i(272, 208), sf::IntRect(sf::Vector2i(0,64), sf::Vector2i(96,32)));
            genSpriteVertices(&vertices[8], sf::Vector2i(400, 208), rectForTilesetId(27));
            target.draw(vertices, states);

            writeCenteredText(wtr("It will give you 10 coins and you will recover 1 life"), 24, 300, target, states);

            break;
        }
        case 4:
        {
            writeCenteredText(wtr("Each new level"), 32, 68, target, states);
            writeCenteredText(wtr("will bring new mechanics"), 32, 100, target, states);
            writeCenteredText(wtr("each time stranger"), 32, 132, target, states);

            sf::VertexArray vertices(sf::Quads);
            vertices.resize(2*4);
            genSpriteVertices(&vertices[0], sf::Vector2i(240, 208), rectForTilesetId(33));
            genSpriteVertices(&vertices[4], sf::Vector2i(368, 208), rectForTilesetId(34));
            target.draw(vertices, states);

            writeCenteredText(wtr("You will need to master them"), 24, 300, target, states);
            break;
        }
        case 5:
        {
            writeCenteredText(wtr("With friends on the same computer"), 32, 68, target, states);
            writeCenteredText(wtr("you can play in the co-op mode"), 32, 100, target, states);
            writeCenteredText(wtr("on the solo levels"), 32, 132, target, states);

            sf::VertexArray vertices(sf::Quads);
            vertices.resize(4*4);
            genSpriteVertices(&vertices[0], sf::Vector2i(208, 208), rectForTilesetId(2));
            genSpriteVertices(&vertices[4], sf::Vector2i(272, 208), rectForTilesetId(3));
            genSpriteVertices(&vertices[8], sf::Vector2i(336, 208), rectForTilesetId(10));
            genSpriteVertices(&vertices[12], sf::Vector2i(400, 208), rectForTilesetId(11));
            target.draw(vertices, states);

            writeCenteredText(wtr("Or try the duel mode with one player controlling a ghost"), 24, 300, target, states);
        }
    }
}

void HelpScreen::updateSize()
{
    sf::Vector2f winSize = _window->getView().getSize();
    _bgVertices = genBackgroundVertices(sf::Vector2u(winSize.x, winSize.y), std::make_pair(0,2));
    _topLeftOffset = 0.5f*winSize - sf::Vector2f(320, 240);
}

void HelpScreen::writeCenteredText(sf::String text, int size, int posY, sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Text cTxt(text, AssetManager::getFont(AssetManager::Gui), size);
    cTxt.setPosition((640-cTxt.getLocalBounds().width)/2, posY);
    target.draw(cTxt, states);
}
