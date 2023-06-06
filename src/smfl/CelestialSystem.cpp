#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class CelestialSystem
{
    private:

        sf::CircleShape * solShape;

        sf::Vector2f velocityMercury;
        double acceleration;

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
        void position(double x, double y);

};

CelestialSystem::CelestialSystem()
{   
    
    solShape = new sf::CircleShape(35);
    solShape->setFillColor(sf::Color::Yellow);
    solShape->setPosition(200,200);

    mercuryShape = new sf::CircleShape(15);
    mercuryShape->setFillColor(sf::Color::Blue);
    position(0, 0);;


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

    window->draw(*solShape);//Dibujar el Sol
    window->draw(*mercuryShape);//Dibujar el Sol

    window->display();
}


void CelestialSystem::position(double x, double y){
    mercuryShape->setPosition(x,y);
    std::cout << x << " " << y << std::endl;
}