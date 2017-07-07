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
            writeCenteredText(L"Bienvenue dans l'aide de Fantômes", 32, 100, target, states);

            writeCenteredText(L"Utilisez les touches flèches pour changer de page", 16, 200, target, states);
            writeCenteredText(L"Appuyez sur <Echap> pour revenir au menu", 16, 220, target, states);

            break;
        }
        case 1:
        {
            writeCenteredText(L"Dans ce jeu vous devez", 32, 68, target, states);
            writeCenteredText(L"attraper un maximum de pièces", 32, 100, target, states);
            writeCenteredText(L"avec le(s) personnage(s)", 32, 132, target, states);

            sf::VertexArray vertices(sf::Quads);
            vertices.resize(3*4);
            genSpriteVertices(&vertices[0], sf::Vector2i(208, 208), rectForTilesetId(2));
            genSpriteVertices(&vertices[4], sf::Vector2i(272, 208), sf::IntRect(sf::Vector2i(0,64), sf::Vector2i(96,32)));
            genSpriteVertices(&vertices[8], sf::Vector2i(400, 208), rectForTilesetId(32));
            target.draw(vertices, states);

            writeCenteredText(L"Chaque pièce vous rapportera 1 point", 24, 300, target, states);

            break;
        }
        case 2:
        {
            writeCenteredText(L"Dans le même temps vous devez", 32, 68, target, states);
            writeCenteredText(L"absolument éviter d'être", 32, 100, target, states);
            writeCenteredText(L"touché par un fantôme", 32, 132, target, states);

            sf::VertexArray vertices(sf::Quads);
            vertices.resize(3*4);
            genSpriteVertices(&vertices[0], sf::Vector2i(208, 208), rectForTilesetId(2));
            genSpriteVertices(&vertices[4], sf::Vector2i(272, 208), sf::IntRect(sf::Vector2i(0,96), sf::Vector2i(96,32)));
            genSpriteVertices(&vertices[8], sf::Vector2i(400, 208), rectForTilesetId(19));
            target.draw(vertices, states);

            writeCenteredText(L"Vous perdriez alors 1 vie", 24, 300, target, states);
            writeCenteredText(L"Attention : Les fantômes ne sont pas tous identiques et ont parfois des capacités spéciales", 16, 350, target, states);

            break;
        }
        case 3:
        {
            writeCenteredText(L"Une fois que vous avez ramassé 30 pièces", 32, 68, target, states);
            writeCenteredText(L"vous pourrez aller au diamant", 32, 100, target, states);
            writeCenteredText(L"pour changer de niveau", 32, 132, target, states);

            sf::VertexArray vertices(sf::Quads);
            vertices.resize(3*4);
            genSpriteVertices(&vertices[0], sf::Vector2i(208, 208), rectForTilesetId(2));
            genSpriteVertices(&vertices[4], sf::Vector2i(272, 208), sf::IntRect(sf::Vector2i(0,64), sf::Vector2i(96,32)));
            genSpriteVertices(&vertices[8], sf::Vector2i(400, 208), rectForTilesetId(27));
            target.draw(vertices, states);

            writeCenteredText(L"Vous gagnez alors 10 points et vous récupérez 1 vie", 24, 300, target, states);

            break;
        }
        case 4:
        {
            writeCenteredText(L"A chaque nouveau niveau", 32, 68, target, states);
            writeCenteredText(L"vous découvrirez de nouveaux mécanismes", 32, 100, target, states);
            writeCenteredText(L"toujours plus étranges", 32, 132, target, states);

            sf::VertexArray vertices(sf::Quads);
            vertices.resize(2*4);
            genSpriteVertices(&vertices[0], sf::Vector2i(240, 208), rectForTilesetId(33));
            genSpriteVertices(&vertices[4], sf::Vector2i(368, 208), rectForTilesetId(34));
            target.draw(vertices, states);

            writeCenteredText(L"Il faudra apprendre à les maîtriser", 24, 300, target, states);
            break;
        }
        case 5:
        {
            writeCenteredText(L"A plusieurs joueurs", 32, 68, target, states);
            writeCenteredText(L"vous pourrez jouer en coopération", 32, 100, target, states);
            writeCenteredText(L"sur les mêmes niveaux qu'en solo", 32, 132, target, states);

            sf::VertexArray vertices(sf::Quads);
            vertices.resize(4*4);
            genSpriteVertices(&vertices[0], sf::Vector2i(208, 208), rectForTilesetId(2));
            genSpriteVertices(&vertices[4], sf::Vector2i(272, 208), rectForTilesetId(3));
            genSpriteVertices(&vertices[8], sf::Vector2i(336, 208), rectForTilesetId(10));
            genSpriteVertices(&vertices[12], sf::Vector2i(400, 208), rectForTilesetId(11));
            target.draw(vertices, states);

            writeCenteredText(L"Ou bien l'un contre l'autre avec le deuxième joueur en fantôme", 24, 300, target, states);
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
