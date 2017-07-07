#include "MenuScreen.h"
#include "GameScreen.h"
#include "HelpScreen.h"
#include "Window.h"
#include "../graphics.h"
#include "../resources/AssetManager.h"
#include "../resources/AudioManager.h"
#include "../game/LevelList.h"
#include "../resources/Settings.h"
#include "../resources/keyboard.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Lock.hpp>

MenuScreen::MenuScreen(Window* w) : Screen(w)
{
    _nbPlayer = 1;
    _levelListId = 0;
    _levelList = LevelList::getLevelList(_levelListId);
    _speedListId = 1;
    _currentKey = -1;
    updateSize();
    setMenu(MainMenu);
    AudioManager::setMusic(AudioManager::Menu);
}

const std::pair<sf::String, float> SPEED_LIST[4] =
{
    std::make_pair(L"Lent (×1)", 1.f), std::make_pair(L"Normal (×1.5)", 1.5f),
    std::make_pair(L"Rapide (×2)", 2.f), std::make_pair(L"Très rapide (×3)", 3.f)
};

void MenuScreen::handleEvent(sf::Event& event)
{
    sf::Lock lock(_mutex); // On s'assure que le traitement des évènements n'empiète pas sur le draw

    if(event.type == sf::Event::KeyPressed && _currentKey == -1)
    {
        switch(event.key.code)
        {
            case sf::Keyboard::Up:
                if(_currentMenu != GameplaySettingsMenu) setCurrentItem(_currentItem-1);
                else setCurrentItem(std::max(0, _currentItem-2));
                break;
            case sf::Keyboard::Down:
                if(_currentMenu != GameplaySettingsMenu) setCurrentItem(_currentItem+1);
                else setCurrentItem(std::min(4, _currentItem+2));
                break;
            case sf::Keyboard::Left:
                if(_currentMenu == PlayMenu)
                {
                    if(_currentItem == 0) setLevelListId(_levelListId-1);
                    else if(_currentItem == 1) setSpeedListId(_speedListId-1);
                    else if(_currentItem == 2) setNbPlayer(_nbPlayer-1);
                }
                else if(_currentMenu == GameplaySettingsMenu) setCurrentItem(_currentItem-1);
                else if(_currentMenu == GraphicSettingsMenu)
                {
                    if(_currentItem == 0) setFrameRate(Settings::frameRate-5);
                    else if(_currentItem == 1) setLightQuality(Settings::lightQuality-1);
                }
                else if(_currentMenu == AudioSettingsMenu)
                {
                    if(_currentItem == 0) setMusicVolume(Settings::musicVolume-5);
                    else if(_currentItem == 1) setSoundVolume(Settings::soundVolume-5);
                }
                break;
            case sf::Keyboard::Right:
                if(_currentMenu == PlayMenu)
                {
                    if(_currentItem == 0) setLevelListId(_levelListId+1);
                    else if(_currentItem == 1) setSpeedListId(_speedListId+1);
                    else if(_currentItem == 2) setNbPlayer(_nbPlayer+1);
                }
                else if(_currentMenu == GameplaySettingsMenu) setCurrentItem(_currentItem+1);
                else if(_currentMenu == GraphicSettingsMenu)
                {
                    if(_currentItem == 0) setFrameRate(Settings::frameRate+5);
                    else if(_currentItem == 1) setLightQuality(Settings::lightQuality+1);
                }
                else if(_currentMenu == AudioSettingsMenu)
                {
                    if(_currentItem == 0) setMusicVolume(Settings::musicVolume+5);
                    else if(_currentItem == 1) setSoundVolume(Settings::soundVolume+5);
                }
                break;
            case sf::Keyboard::Space:
            case sf::Keyboard::Return:
                switch(_currentMenu)
                {
                    case MainMenu:
                        if(_currentItem == 0) setMenu(PlayMenu);
                        else if(_currentItem == 1) setMenu(SettingsMenu);
                        else if(_currentItem == 2) _window->setScreen(new HelpScreen(_window));
                        else if(_currentItem == 3) _window->close();
                        break;
                    case PlayMenu:
                        if(_currentItem == 3) _window->setScreen(new GameScreen(_nbPlayer, _levelListId, SPEED_LIST[_speedListId].second, _window));
                        else if(_currentItem == 4) setMenu(MainMenu);
                        break;
                    case SettingsMenu:
                        if(_currentItem == 0) setMenu(GameplaySettingsMenu);
                        else if(_currentItem == 1) setMenu(GraphicSettingsMenu);
                        else if(_currentItem == 2) setMenu(AudioSettingsMenu);
                        else if(_currentItem == 3) setMenu(MainMenu);
                        break;
                    case GameplaySettingsMenu:
                        if(_currentItem == 4)
                        {
                            Settings::saveSettings();
                            setMenu(SettingsMenu);
                            setCurrentItem(3);
                        }
                        else _currentKey = 0;
                        break;
                    case GraphicSettingsMenu:
                        if(_currentItem == 2)
                        {
                            Settings::saveSettings();
                            setMenu(SettingsMenu);
                            setCurrentItem(3);
                        }
                        break;
                    case AudioSettingsMenu:
                        if(_currentItem == 2)
                        {
                            Settings::saveSettings();
                            setMenu(SettingsMenu);
                            setCurrentItem(3);
                        }
                        break;
                }
                break;
            default:
                break;
        }
    }
    else if(event.type == sf::Event::KeyPressed)
    {
        Settings::controls[_currentItem].keys[_currentKey] = event.key.code;
        _currentKey++;
        if(_currentKey == 4) _currentKey = -1;
    }
}

void MenuScreen::drawLabel(sf::String labelString, int yPos, sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Text label(labelString, AssetManager::getFont(AssetManager::Gui), 32);
    label.setPosition(centerToSide(320,label.getLocalBounds().width), yPos);
    label.setFillColor(sf::Color::White);
    target.draw(label, states);
}

void MenuScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Lock lock(_mutex);

    states.texture = AssetManager::getTileset(AssetManager::Background);
    target.draw(_bgVertices, states);

    states.transform.translate(_topLeftOffset);
    for(unsigned i = 0 ; i < _menuItems.size() ; i++) target.draw(_menuItems[i], states);

    if(_currentMenu == PlayMenu)
    {
        drawLabel(_levelList->name, 48, target, states);
        drawLabel(SPEED_LIST[_speedListId].first, 128, target, states);

        sf::VertexArray nbPlayerVertices(sf::Quads);
        nbPlayerVertices.resize(4*_nbPlayer);
        for(int i = 0 ; i < _nbPlayer ; i++)
        {
            genSpriteVertices(&nbPlayerVertices[i*4], sf::Vector2i(144+(2*i+1)*320/(2*_nbPlayer), 212), rectForTilesetId(i*8));
        }
        states.texture = AssetManager::getTileset(AssetManager::Sprite);
        target.draw(nbPlayerVertices, states);
    }
    else if(_currentMenu == GraphicSettingsMenu)
    {
        const sf::String LIGHT_QUALITY_NAME[2] = { L"Basse", L"Elevée" };
        drawLabel(std::to_string(Settings::frameRate)+" fps", 112, target, states);
        drawLabel(LIGHT_QUALITY_NAME[Settings::lightQuality], 208, target, states);
    }
    else if(_currentMenu == AudioSettingsMenu)
    {
        drawLabel(std::to_string(Settings::musicVolume)+"%", 112, target, states);
        drawLabel(std::to_string(Settings::soundVolume)+"%", 208, target, states);
    }
    else if(_currentMenu == GameplaySettingsMenu)
    {
        const sf::IntRect keyBackground = sf::IntRect(sf::Vector2i(128,0), sf::Vector2i(48,48));
        const sf::IntRect selectedKeyBackground = sf::IntRect(sf::Vector2i(128,48), sf::Vector2i(48,48));
        sf::VertexArray vertices(sf::Quads);
        vertices.resize(64);
        sf::Text keyName[16];
        for(int i = 0 ; i < 4 ; i++)
        {
            const sf::Vector2i offset = sf::Vector2i(centerToSide(640*(1+2*(i%2))/4, 160), 80 + (i/2)*176);
            const sf::Vector2i KEY_POSITION[4] = { sf::Vector2i(8, 48), sf::Vector2i(104, 48), sf::Vector2i(56, 0), sf::Vector2i(56, 48) };

            for(int j = 0 ; j < 4 ; j++)
            {
                if(i != _currentItem || j != _currentKey) genSpriteVertices(&vertices[i*16+j*4], KEY_POSITION[j] + offset, keyBackground);
                else genSpriteVertices(&vertices[i*16+j*4], KEY_POSITION[j] + offset, selectedKeyBackground);

                sf::String keyChar = keyToChar(Settings::controls[i].keys[j]);
                keyName[4*i+j].setString(keyChar);
                keyName[4*i+j].setFont(AssetManager::getFont(AssetManager::Keyboard));
                keyName[4*i+j].setFillColor(sf::Color::White);
                if(keyChar.getSize() == 1) keyName[4*i+j].setCharacterSize(32);
                else keyName[4*i+j].setCharacterSize(16);
                sf::FloatRect textBound = keyName[4*i+j].getLocalBounds();
                keyName[4*i+j].setPosition(sf::Vector2f(centerToSide(KEY_POSITION[j].x + 24 + offset.x, textBound.left+textBound.width),
                                                        centerToSide(KEY_POSITION[j].y + 16 + offset.y, textBound.top+textBound.height)));
            }
        }
        states.texture = AssetManager::getTileset(AssetManager::HelpSettings);
        target.draw(vertices, states);
        for(int i = 0 ; i < 16 ; i++) target.draw(keyName[i], states);
    }
}

void MenuScreen::updateSize()
{
    sf::Vector2f winSize = _window->getView().getSize();
    _bgVertices = genBackgroundVertices(sf::Vector2u(winSize.x, winSize.y), std::make_pair(48,2));
    _topLeftOffset = 0.5f*winSize - sf::Vector2f(320, 240);
}

const std::tuple<sf::String, int, int> MAIN_MENU_ITEMS[4] =
{
    std::make_tuple(L"Jouer", 128, 32),
    std::make_tuple(L"Options", 64, 192),
    std::make_tuple(L"Aide", 64, 272),
    std::make_tuple(L"Quitter", 64, 352)
};

const std::tuple<sf::String, int, int> PLAY_MENU_ITEMS[5] =
{
    std::make_tuple(L"Niveaux :", 32, 16),
    std::make_tuple(L"Vitesse :", 32, 96),
    std::make_tuple(L"Nombre de joueurs :", 32, 176),
    std::make_tuple(L"Commencer !", 64, 272),
    std::make_tuple(L"Retour", 32, 400)
};

const std::tuple<sf::String, int, int> SETTINGS_MENU_ITEMS[4] =
{
    std::make_tuple(L"Gameplay", 64, 32),
    std::make_tuple(L"Graphisme", 64, 128),
    std::make_tuple(L"Audio", 64, 224),
    std::make_tuple(L"Retour", 64, 352)
};

const std::tuple<sf::String, int, int> GAMEPLAY_SETTINGS_MENU_ITEMS[5] =
{
    std::make_tuple(L"J1", 32, 32),
    std::make_tuple(L"J2", 32, 32),
    std::make_tuple(L"J3", 32, 208),
    std::make_tuple(L"J4", 32, 208),
    std::make_tuple(L"Valider", 64, 384)
};

const std::tuple<sf::String, int, int> GRAPHIC_SETTINGS_MENU_ITEMS[3] =
{
    std::make_tuple(L"Fréquence de rafraîchissement :", 32, 80),
    std::make_tuple(L"Qualité des lumières :", 32, 176),
    std::make_tuple(L"Valider", 64, 304)
};

const std::tuple<sf::String, int, int> AUDIO_SETTINGS_MENU_ITEMS[3] =
{
    std::make_tuple(L"Volume de la musique :", 32, 80),
    std::make_tuple(L"Volume des sons :", 32, 176),
    std::make_tuple(L"Valider", 64, 304)
};

void MenuScreen::setMenu(Menu menu)
{
    _menuItems.clear();
    _currentItem = 0;
    _currentMenu = menu;

    int nbItems = 0;
    const std::tuple<sf::String, int, int>* itemParams = nullptr;
    switch(menu)
    {
        case MainMenu:
            nbItems = 4;
            itemParams = MAIN_MENU_ITEMS;
            break;
        case PlayMenu:
            nbItems = 5;
            itemParams = PLAY_MENU_ITEMS;
            break;
        case SettingsMenu:
            nbItems = 4;
            itemParams = SETTINGS_MENU_ITEMS;
            break;
        case GameplaySettingsMenu:
            nbItems = 5;
            itemParams = GAMEPLAY_SETTINGS_MENU_ITEMS;
            break;
        case GraphicSettingsMenu:
            nbItems = 3;
            itemParams = GRAPHIC_SETTINGS_MENU_ITEMS;
            break;
        case AudioSettingsMenu:
            nbItems = 3;
            itemParams = AUDIO_SETTINGS_MENU_ITEMS;
            break;
    }

    for(int i = 0 ; i < nbItems ; i++)
    {
        sf::Text item(std::get<0>(itemParams[i]), AssetManager::getFont(AssetManager::Gui), std::get<1>(itemParams[i]));
        if(menu != GameplaySettingsMenu || i == 4)
            item.setPosition(centerToSide(320, item.getLocalBounds().width), std::get<2>(itemParams[i]));
        else
            item.setPosition(centerToSide(640*(1+2*(i%2))/4, item.getLocalBounds().width), std::get<2>(itemParams[i]));
        item.setFillColor(sf::Color::Black);
        _menuItems.push_back(item);
    }
    setCurrentItem(0);
}

void MenuScreen::setCurrentItem(int currentItem)
{
    if(currentItem < 0) currentItem += _menuItems.size();
    currentItem %= _menuItems.size();

    _menuItems[_currentItem].setFillColor(sf::Color::Black);
    _menuItems[currentItem].setFillColor(sf::Color::White);
    _currentItem = currentItem;
}

void MenuScreen::setLevelListId(int id)
{
    if(id < 0) id += LevelList::nbLevelList();
    id %= LevelList::nbLevelList();
    _levelListId = id;
    _levelList = LevelList::getLevelList(id);

    _nbPlayer = std::max(_nbPlayer, _levelList->playerMinMax.first);
    _nbPlayer = std::min(_nbPlayer, _levelList->playerMinMax.second);
}

void MenuScreen::setSpeedListId(int id)
{
    _speedListId = id;
    _speedListId = std::max(_speedListId, 0);
    _speedListId = std::min(_speedListId, 3);
}

void MenuScreen::setNbPlayer(int nb)
{
    _nbPlayer = nb;
    _nbPlayer = std::max(_nbPlayer, _levelList->playerMinMax.first);
    _nbPlayer = std::min(_nbPlayer, _levelList->playerMinMax.second);
}

void MenuScreen::setFrameRate(int fps)
{
    fps = std::max(25, fps);
    fps = std::min(120, fps);
    Settings::setFrameRate(fps);
}

void MenuScreen::setLightQuality(int quality)
{
    quality = std::max(0, quality);
    quality = std::min(1, quality);
    Settings::lightQuality = quality;
}

void MenuScreen::setMusicVolume(int volume)
{
    volume = std::max(0, volume);
    volume = std::min(100, volume);
    Settings::musicVolume = volume;
    AudioManager::setMusicVolume(volume);
}

void MenuScreen::setSoundVolume(int volume)
{
    volume = std::max(0, volume);
    volume = std::min(100, volume);
    Settings::soundVolume = volume;
}
