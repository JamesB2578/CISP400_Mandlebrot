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
    double aspectRatio = resolution.y / resolution.x;
    VideoMode vm(resolution.x, resolution.y);
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Mandlebrot Set", Style::Default);

    ComplexPlane plane(aspectRatio);

    Text hud;
    hud.setPosition(0, 0);
    hud.setFillColor(Color::White);
    hud.setCharacterSize(25);
    Font font;
    font.loadFromFile("fonts/specialagent.ttf");
    hud.setFont(font);
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
                Vector2f points = window.mapPixelToCoords(Mouse::getPosition(window), plane.getView());
                plane.setMouseLoactaion(points);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    plane.zoomOut();
                    Vector2f cenPoints = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y), plane.getView());
                    plane.setCenter(cenPoints);
                }

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    plane.zoomIn();
                    Vector2f cenPoints = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y), plane.getView());
                    plane.setCenter(cenPoints);
                }
                state = State::CALCULATING;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Update Scene
        if (state == State::CALCULATING)
        {
            //Calculation 
            //two for-loops to check every pixel accross the screen
            for (int j = 0; j < resolution.x; j++)
            {
                for (int i = 0; i < resolution.y ; i++)
                {
                    Uint8 R;
                    Uint8 G;
                    Uint8 B;
                    size_t iter;
                    image[j + i * resolution.x].position = { (float)j, (float)i };
                    Vector2f pixelLocation = window.mapPixelToCoords(Vector2i(j, i), plane.getView());
                    iter = plane.countIterations(pixelLocation);
                    plane.iterationsToRGB(iter, R, G, B);
                    image[j + i * resolution.x].color = { R, G, B };
                    cout << iter << endl;
                    //cout << image[i].position.x << endl;
                    //cout << "Color: " << image[j + i * resolution.x].color.r << " " << image[j + i * resolution.x].color.g << " " << image[j + i * resolution.x].color.b << endl;

                }
            }
            state = State::DISPLAYING;
        }


        plane.loadText(hud);

        // Draw Scene
        if (state == State::DISPLAYING)
        {
            window.clear();
            window.draw(image);
            window.draw(hud);
            window.display();
        }



    }

    return 0;
}
