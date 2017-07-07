#include "Settings.h"
#include <fstream>

Controls Settings::controls[4] =
{
    {Controls::Type::Keyboard,{sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down}},
    {Controls::Type::Keyboard,{sf::Keyboard::Q, sf::Keyboard::D, sf::Keyboard::Z, sf::Keyboard::S}},
    {Controls::Type::Keyboard,{sf::Keyboard::Numpad1, sf::Keyboard::Numpad3, sf::Keyboard::Numpad5, sf::Keyboard::Numpad2}},
    {Controls::Type::Keyboard,{sf::Keyboard::J, sf::Keyboard::L, sf::Keyboard::I, sf::Keyboard::K}}
};

int Settings::frameRate = 60;
float Settings::frameTime = 1.f/60;
int Settings::lightQuality = 1;

int Settings::musicVolume = 50;
int Settings::soundVolume = 100;

void Settings::setFrameRate(int fps)
{
    frameRate = fps;
    frameTime = 1.f/fps;
}

void Settings::loadSettings()
{
    std::ifstream configFile;
    configFile.open("settings.cfg");
    if(!configFile)
    {
        saveSettings();
        return;
    }

    for(int i = 0 ; i < 4 ; i++)
    {
        char controlType;
        configFile >> controlType;
        controls[i].type = static_cast<Controls::Type>(controlType);

        if(controls[i].type == Controls::Type::Keyboard)
        {
            for(int dir = 0 ; dir < 4 ; dir++)
            {
                int key;
                configFile >> key;
                controls[i].keys[dir] = static_cast<sf::Keyboard::Key>(key);
            }
        }

        configFile.ignore(1,'\n');
    }

    configFile >> frameRate;
    configFile >> lightQuality;

    configFile >> musicVolume;
    configFile >> soundVolume;

    configFile.close();
}

void Settings::saveSettings()
{
    std::ofstream configFile;
    configFile.open("settings.cfg");
    if(!configFile) return;

    for(int i = 0 ; i < 4 ; i++)
    {
        configFile << static_cast<char>(controls[i].type);

        if(controls[i].type == Controls::Type::Keyboard)
        {
            for(int dir = 0 ; dir < 4 ; dir++)
            {
                configFile << ' ' << static_cast<int>(controls[i].keys[dir]);
            }
        }
        configFile << '\n';
    }

    configFile << frameRate << '\n';
    frameTime = 1.f/frameRate;
    configFile << lightQuality << '\n';

    configFile << musicVolume << '\n';
    configFile << soundVolume << '\n';

    configFile.close();
}
