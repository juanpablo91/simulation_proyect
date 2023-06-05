#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "./Sol.cpp"
#include "./Mercury.cpp"

class CelestialSystem
{
    private:
        Sol sol;
        sf::CircleShape * solShape;

        sf::Vector2f velocityMercury;
        double acceleration;
        Mercury mercury;
        sf::CircleShape * mercuryShape;
        

        sf::RenderWindow * window;
        int width;
        int height;
        std::string title;
        sf::Event * event1;
        int fps;    
    
    public:
        CelestialSystem();
        void loop();
        void processEvent();
        void _draw();

};

CelestialSystem::CelestialSystem()
{   
    
    sol.circle = new sf::CircleShape(32);
    sol.circle->setFillColor(sf::Color::Yellow);
    sol.circle->setPosition(200,200);

    mercury.circle = new sf::CircleShape(32);
    mercury.circle->setFillColor(sf::Color::Yellow);
    mercury.circle->setPosition(200,200);

    //solShape = sol.circle;

    width = 800;
    width = 600; 
    height = 600;
    title = "Simulacion Sol-Mercurio";

    window = new sf::RenderWindow(sf::VideoMode(width,height),title);
    fps = 60;
    window->setFramerateLimit(fps);
    event1 = new sf::Event();

    loop();
    std::cout << "Finished." << std::endl;

};


void CelestialSystem::loop()
{
    while (window->isOpen())
    {
        
        processEvent();
        _draw();
        
    }
}

void CelestialSystem::processEvent(){
    while (window->pollEvent(*event1))
    {   
        switch (event1->type)
        {   
        case sf::Event::Closed:
            window->close();
            exit(1);
            break;
    
        default:
            break;
        }
 
    }

}

void CelestialSystem::_draw()
{
    window->clear();

    window->draw(*sol.circle);//Dibujar el Sol
    window->draw(*mercuryShape);//Dibujar el Sol

    window->display();
}