#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics/Drawable.hpp>
#include "../common.h"
namespace sf { class Event; }
class Window;

class Screen : public sf::Drawable
{
public:
    Screen(Window* w) { _window = w; }
    ~Screen() = default;
    virtual sf::Vector2u wantedSize() const { return sf::Vector2u(640, 480); }
    virtual void handleEvent(sf::Event&) {}
    virtual void step() {}
    virtual bool prepareDraw() { return true; }
    virtual void updateSize() {}
    void draw(sf::RenderTarget&, sf::RenderStates) const override {}
protected:
    Window* _window;
};

#endif // SCREEN_H

