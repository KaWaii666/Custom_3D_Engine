#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Engine.h"



using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::cin;




int main()
{



    int size[2] = {1920, 1080};
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    sf::RenderWindow window(sf::VideoMode(size[0], size[1]), "Custom 3D Engine", sf::Style::Default, settings);
    sf::View Origin(sf::FloatRect(-size[0] / 2, -size[1] / 2, size[0], size[1]));
    window.setVerticalSyncEnabled(true);

    window.setView(Origin);



    
    float side = 300;
    float length = 300;

    



    Shape shape = PyramidShape(side);


    Projector projector;
    projector.LoadShape(shape);
    projector.setDistance(1);
    projector.LoadAdjacencyMatrix(PYRAMIDADJACENCY);
    projector.showPoint(true, 5, sf::Color::Yellow);
    


    float angleX = 0.f;
    float angleY = 0.f;
    float angleZ = 0.f;
    
    float RotationSpeed = 0.6f;

    sf::Clock clock;
    Clock CustomTimer(1.f);


    float dt = 0;

    float fps = 0;

    bool Dpressed = false;
    bool Zpressed = false;
    bool Qpressed = false;
    bool Spressed = false;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::D)
                {
                    Dpressed = true;
                }
                else if (event.key.code == sf::Keyboard::Z)
                {
                    Zpressed = true;
                }
                else if (event.key.code == sf::Keyboard::Q)
                {
                    Qpressed = true;
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    Spressed = true;
                }
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::D)
                {
                    Dpressed = false;
                }
                else if (event.key.code == sf::Keyboard::Z)
                {
                    Zpressed = false;
                }
                else if (event.key.code == sf::Keyboard::Q)
                {
                    Qpressed = false;
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    Spressed = false;
                }
            }


        }


        window.clear();
        DrawPoint(window, sf::Vector2f(0, 0), sf::Color::Red, 2.f);
        

        
        projector.draw(window);
        if (CustomTimer.doTriggered())
        {
            
            fps = 1 / dt;
            CustomTimer.reset(false);

        }
        displayText(window, sf::Vector2f(-size[0] / 2, -size[1] / 2), "./assets/fonts/NewShape-Book.ttf", std::to_string(std::round(fps)), 30, sf::Color::Red);
        window.display();

        
        dt = clock.restart().asSeconds();
        
        CustomTimer.update(dt);
        
        if (Zpressed)
        {
            angleX += RotationSpeed;
        }
        if (Dpressed)
        {
            angleY += RotationSpeed;
        }
        if (Qpressed)
        {
            angleZ += RotationSpeed;
        }
        if (Spressed)
        {
            angleX -= RotationSpeed;
        }

        //cout << "Angle X: " << angleX << endl;
        
        
        projector.setAngle(angleX, angleY, angleZ);
    
    }






}
