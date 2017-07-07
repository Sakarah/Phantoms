#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "common.h"
namespace sf
{
    class Sound;
    class SoundBuffer;
    class Music;
}

const int MAX_SOUND_NB = 8;

class AudioManager
{
public:
    enum Music
    {
        Silence,
        Menu,
        Level,
        Bonus,
        Boss,
        Duel,
        GameOver,
        Victory,
        NbMusic // Keep at end !
    };

    enum Sound
    {
        Touched,
        Explosion,
        Gold,
        Crystal,
        Life,
        Teleport,
        Switch,
        Power,
        SwordTaken,
        SwordHit,
        BossDie,
        Slowed,
        NbSounds // Keep at end !
    };

    static void init();
    static void playSound(Sound);
    static void setMusic(Music, bool repeat = true);
    static void setMusicVolume(int);

private:
    static int _nextSound;
    static sf::Sound _sounds[MAX_SOUND_NB];
    static sf::SoundBuffer _soundBuffers[NbSounds];
    static sf::Music _music;
};

#endif // AUDIOMANAGER_H
