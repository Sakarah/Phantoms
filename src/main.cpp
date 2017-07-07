#include "resources/ReplayRecorder.h"
#include "resources/Settings.h"
#include "Random.h"
#include "game/LevelList.h"
#include "resources/AssetManager.h"
#include "resources/AudioManager.h"
#include "window/Window.h"
#include "window/MenuScreen.h"
#include "window/GameScreen.h"

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");
    bindtextdomain("phantoms", "i18n");
    textdomain("phantoms");

    ReplayRecorder::ReplayMode replayMode = ReplayRecorder::Record;
    std::string replayFile = "replay.rec";
    bool loadSettings = true;
    for(int i = 1 ; i < argc ; i++)
    {
        std::string arg = argv[i];
        if(arg == "-n" || arg == "--no-record") replayMode = ReplayRecorder::Disabled;
        else if(arg == "-r" || arg == "--replay")
        {
            replayMode = ReplayRecorder::Replay;
            if(i+1 < argc && argv[i+1][0] != '-')
            {
                replayFile = argv[i+1];
                i++;
            }
        }
        else if(arg == "-R" || arg == "--record")
        {
            if(i+1 < argc && argv[i+1][0] != '-')
            {
                replayFile = argv[i+1];
                i++;
            }
        }
        else if(arg == "-d" || arg == "--default-settings") loadSettings = false;
    }

    if(loadSettings) Settings::loadSettings();
    ReplayRecorder::init(replayMode, replayFile);
    Random::initRandEngine();
    LevelList::loadLists();
    AssetManager::loadAssets();
    AudioManager::init();

    Window window;
    if(replayMode == ReplayRecorder::Replay) window.setScreen(new GameScreen(0, 0, 0, &window));
    else window.setScreen(new MenuScreen(&window));
    window.loop();

    return 0;
}
