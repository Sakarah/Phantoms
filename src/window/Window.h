#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "../common.h"
class Screen;

class Window : public sf::RenderWindow
{
public:
    Window();
    ~Window() = default;
    void setScreen(Screen*);
    void updateSize();
    void startMultithreadLoops();
    void startMonothreadLoop();
    void manageEvent(sf::Event&);
    void stepLoop();
    void step(sf::Clock&);
    void drawLoop();
    void render();
private:
    shared_ptr<Screen> _screen;
    bool _haveFocus;
    bool _updateSize;
};

#endif // WINDOW_H
