#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <SFML/Window/Keyboard.hpp>

struct Controls
{
    enum class Type : char
    {
        Keyboard = 'K'
    };
    Type type;
    union
    {
        sf::Keyboard::Key keys[4];
    };
};

namespace Settings
{
    void loadSettings();
    void saveSettings();

    extern Controls controls[4];
    extern int frameRate;
    extern float frameTime;
    void setFrameRate(int);
    extern int lightQuality;
    extern int musicVolume;
    extern int soundVolume;

}

#endif // SETTINGMANAGER_H
