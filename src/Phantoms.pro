TEMPLATE = app
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11 -fno-rtti -fno-exceptions -pedantic

SOURCES += \
    game/objects/Boss.cpp \
    game/objects/Character.cpp \
    game/objects/CharacterPhantom.cpp \
    game/objects/Object.cpp \
    game/objects/Phantom.cpp \
    game/objects/Powerup.cpp \
    game/objects/Switch.cpp \
    game/objects/Teleporter.cpp \
    game/objects/Wall.cpp \
    game/paths/LinearPath.cpp \
    game/paths/Path.cpp \
    game/paths/QuadraticPath.cpp \
    game/views/Background.cpp \
    game/views/Border.cpp \
    game/views/Foreground.cpp \
    game/views/LightComposer.cpp \
    game/views/LightSource.cpp \
    game/views/SpriteView.cpp \
    game/ContactManager.cpp \
    game/EmptySpaceChecker.cpp \
    game/Game.cpp \
    game/LevelList.cpp \
    game/LevelLoader.cpp \
    game/NearestObjectRaycaster.cpp \
    game/VerticesLister.cpp \
    game/WarpChecker.cpp \
    game/World.cpp \
    resources/AssetManager.cpp \
    resources/AudioManager.cpp \
    resources/ReplayRecorder.cpp \
    resources/Settings.cpp \
    window/EndScreen.cpp \
    window/GameScreen.cpp \
    window/HelpScreen.cpp \
    window/MenuScreen.cpp \
    window/Window.cpp \
    graphics.cpp \
    main.cpp \
    Random.cpp

HEADERS += \
    game/objects/Boss.h \
    game/objects/Character.h \
    game/objects/CharacterPhantom.h \
    game/objects/Object.h \
    game/objects/Phantom.h \
    game/objects/Powerup.h \
    game/objects/Switch.h \
    game/objects/Teleporter.h \
    game/objects/Wall.h \
    game/paths/LinearPath.h \
    game/paths/Path.h \
    game/paths/QuadraticPath.h \
    game/views/Background.h \
    game/views/Border.h \
    game/views/Foreground.h \
    game/views/LightComposer.h \
    game/views/LightSource.h \
    game/views/SpriteView.h \
    game/ContactManager.h \
    game/EmptySpaceChecker.h \
    game/Game.h \
    game/gameplay.h \
    game/LevelList.h \
    game/LevelLoader.h \
    game/NearestObjectRaycaster.h \
    game/VerticesLister.h \
    game/WarpChecker.h \
    game/World.h \
    resources/AssetManager.h \
    resources/AudioManager.h \
    resources/keyboard.h \
    resources/ReplayRecorder.h \
    resources/Settings.h \
    window/EndScreen.h \
    window/GameScreen.h \
    window/HelpScreen.h \
    window/MenuScreen.h \
    window/Screen.h \
    window/Window.h \
    common.h \
    graphics.h \
    Random.h

CONFIG(debug, debug|release) {
    DEFINES += DEBUG
    SOURCES += game/views/PhysicsDebugDraw.cpp
    HEADERS += game/views/PhysicsDebugDraw.h
}

RC_FILE += win32.rc

# Dépendance SFML
windows {
    INCLUDEPATH += ../../libs/SFML-2.3/include
    LIBS += -L../../libs/SFML-2.3/lib/
    CONFIG(release, debug|release): LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
    CONFIG(debug, debug|release): LIBS += -lsfml-system-d -lsfml-window-d -lsfml-graphics-d -lsfml-audio-d
}
unix: LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

# Dépendance Box2D
windows {
    INCLUDEPATH += ../../libs/Box2D/include
    CONFIG(release, debug|release): LIBS += -L../../libs/Box2D/bin/release/ -lBox2D
    CONFIG(debug, debug|release): LIBS += -L../../libs/Box2D/bin/debug/ -lBox2D
}
unix : LIBS += -lBox2D

# Dépendance TmxParser
LIBS += -ltmxparser
