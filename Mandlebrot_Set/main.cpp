#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <complex>
#include "ComplexPlane.h"
using namespace std;
using namespace sf;


int main()
{
    // Create variables and store resolution and aspectRatio
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    double aspectRatio = resolution.y / resolution.x;

    // Create window
    VideoMode vm(resolution.x, resolution.y);
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Mandlebrot Set", Style::Default);

    // object with ComplexPlane class
    ComplexPlane plane(aspectRatio);

    // Create and set text object for heads up display
    Text hud;
    hud.setPosition(0, 0);
    hud.setFillColor(Color::White);
    hud.setCharacterSize(25);

    // Create font object and apply to text
    Font font;
    font.loadFromFile("fonts/KGRedHands.ttf");
    hud.setFont(font);

    // Create vertex array
    VertexArray image;
    image.setPrimitiveType(Points);
    image.resize(resolution.x * resolution.y);

    // enum class that allows program to do certain task under certain states;
    enum class State {
        CALCULATING, DISPLAYING
    };

    State state = State::CALCULATING;

    // Main loop
    while (window.isOpen())
    {
        // Handle input
        Event event;
        while (window.pollEvent(event))
        {
            // close windwo when user hits x button
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            //update mouse location for HUD
            if (event.type == sf::Event::MouseMoved)
            {
                Vector2f points = window.mapPixelToCoords(Mouse::getPosition(window), plane.getView());
                plane.setMouseLoactaion(points);
            }

            // Detect clicks to either zoom in or zoom out
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

        // close if user hits escape
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Update Scene
        if (state == State::CALCULATING)
        {
            //Calculation 
            //set each pixel to a color based on number of iterations
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
                    //cout << iter << endl;
                }
            }
            state = State::DISPLAYING;
        }

        // load text from ComplexPlane class
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
