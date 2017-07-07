#include "AudioManager.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include "Settings.h"

int AudioManager::_nextSound;
sf::Sound AudioManager::_sounds[MAX_SOUND_NB];
sf::SoundBuffer AudioManager::_soundBuffers[NbSounds];
sf::Music AudioManager::_music;

const std::string MUSIC_FILE[AudioManager::NbMusic] = {"", "menu.ogg", "level.ogg", "bonus.ogg", "boss.ogg", "duel.ogg", "gameOver.ogg",
                                                       "victory.ogg"};
const std::string SOUND_FILE[AudioManager::NbSounds] = {"touched.ogg", "explosion.ogg", "gold.ogg", "cristal.ogg", "life.ogg",
                                                        "teleport.ogg", "switch.ogg", "power.ogg", "swordTaken.ogg", "swordHit.ogg",
                                                        "bossDie.ogg", "slowed.ogg"};
void AudioManager::init()
{
    _nextSound = 0;
    for(int i = 0 ; i < NbSounds ; i++) _soundBuffers[i].loadFromFile("assets/sound/"+SOUND_FILE[i]);
    _music.setVolume(Settings::musicVolume);
}

void AudioManager::playSound(AudioManager::Sound sound)
{
    _sounds[_nextSound].stop();
    _sounds[_nextSound].setBuffer(_soundBuffers[sound]);
    _sounds[_nextSound].setVolume(Settings::soundVolume);
    _sounds[_nextSound].play();

    _nextSound++;
    _nextSound %= MAX_SOUND_NB;
}

void AudioManager::setMusic(AudioManager::Music music, bool repeat)
{
    _music.stop();
    if(music == Silence) return;
    _music.openFromFile("assets/music/"+MUSIC_FILE[music]);
    _music.setLoop(repeat);
    _music.play();
}

void AudioManager::setMusicVolume(int volume)
{
    _music.setVolume(volume);
}
