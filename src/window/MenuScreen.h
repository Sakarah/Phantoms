#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "Screen.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Mutex.hpp>
class LevelList;
namespace sf { class String; }

class MenuScreen : public Screen
{
public:
    MenuScreen(Window*);
    ~MenuScreen() = default;
    void handleEvent(sf::Event&) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void updateSize() override;

private:
    enum Menu
    {
        MainMenu,
        PlayMenu,
        SettingsMenu,
        GameplaySettingsMenu,
        GraphicSettingsMenu,
        AudioSettingsMenu
    };

    void setMenu(Menu);
    void setCurrentItem(int);
    void setLevelListId(int);
    void setSpeedListId(int);
    void setNbPlayer(int);
    void setFrameRate(int);
    void setLightQuality(int);
    void setMusicVolume(int);
    void setSoundVolume(int);

    void drawLabel(sf::String labelString, int yPos, sf::RenderTarget& target, sf::RenderStates states) const;

    Menu _currentMenu;
    int _currentItem;
    int _nbPlayer;
    int _levelListId;
    const LevelList* _levelList;
    int _speedListId;
    int _currentKey;

    sf::VertexArray _bgVertices;
    sf::Vector2f _topLeftOffset;
    std::vector<sf::Text> _menuItems;
    mutable sf::Mutex _mutex;
};

#endif // MENUSCREEN_H
