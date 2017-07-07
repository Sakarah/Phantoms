#include "Window.h"
#include "Screen.h"
#include "../resources/Settings.h"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

Window::Window() : sf::RenderWindow(sf::VideoMode(800, 608), wtr("Phantoms"), sf::Style::Default)
{
    sf::Image windowIcon;
    windowIcon.loadFromFile("assets/icon.png");
    setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());

    _screen = shared_ptr<Screen>(new Screen(this));
    _haveFocus = true;
    _updateSize = false;
}

void Window::setScreen(Screen* newMode)
{
    _screen = shared_ptr<Screen>(newMode);
    _updateSize = true;
}

void Window::updateSize()
{
    _updateSize = true;
}

void Window::loop()
{
    sf::Clock stepClock;
    while(isOpen())
    {
        sf::Event event;
        while(pollEvent(event)) manageEvent(event);

        sf::Time elapsedTime = stepClock.getElapsedTime();
        if(elapsedTime.asSeconds() < Settings::frameTime) continue;
        stepClock.restart();

        step();
        render();
    }
}

void Window::manageEvent(sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::Closed:
            close();
            break;
        case sf::Event::LostFocus:
            _haveFocus = false;
            break;
        case sf::Event::GainedFocus:
            _haveFocus = true;
            break;
        case sf::Event::Resized:
            _updateSize = true;
            break;
        default:
            shared_ptr<Screen> screen = _screen;
            screen->handleEvent(event);
            break;
    }
}

void Window::step()
{
    if(!_haveFocus) return;

    shared_ptr<Screen> screen = _screen;
    screen->step();
}

void Window::render()
{
    shared_ptr<Screen> screen = _screen;

    if(_updateSize)
    {
        sf::Vector2u minSize = _screen->wantedSize();
        sf::Vector2u currentSize = getSize();
        sf::Vector2u finalSize = sf::Vector2u(std::max(minSize.x, currentSize.x), std::max(minSize.y, currentSize.y));
        setSize(finalSize);
        currentSize = getSize();
        if(currentSize.x >= minSize.x && currentSize.y >= minSize.y) setView(sf::View(sf::FloatRect(0,0,currentSize.x,currentSize.y)));
        else
        {
            float factor = std::max(minSize.x/float(currentSize.x), minSize.y/float(currentSize.y));
            setView(sf::View(sf::FloatRect(0,0,currentSize.x*factor,currentSize.y*factor)));
        }
        screen->updateSize();
        _updateSize = false;
    }

    screen->prepareDraw();
    clear();
    draw(*screen);
    display();
}
