#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <complex>
#include "ComplexPlane.h"
using namespace std;
using namespace sf;


int main()
{
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    float aspectRatio = resolution.y / resolution.x;
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Mandlebrot Set", Style::Fullscreen);

    ComplexPlane comPlane(aspectRatio);

    Text hud;
    Font font;
    font.loadFromFile("fonts/specialagent.ttf");
    VertexArray image;
    image.setPrimitiveType(Points);
    image.resize(resolution.x * resolution.y);
    enum class State {
        CALCULATING, DISPLAYING
    };

    State state = State::CALCULATING;

    while (window.isOpen())
    {
        // Handle input
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved)
            {
                comPlane.setMouseLoactaion()
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    comPlane.zoomOut();
                    comPlane.setCenter(Vector2f(event.mouseButton.x, event.mouseButton.y));
                }

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    comPlane.zoomIn();
                    comPlane.setCenter(Vector2f(event.mouseButton.x, event.mouseButton.y));
                }
            }
        }
    }

    return 0;
}
