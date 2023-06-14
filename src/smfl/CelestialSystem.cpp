#pragma once

#include <iostream>
#include "Button.cpp"

class CelestialSystem
{
    private:

        //bodys
        sf::CircleShape * solShape;

        sf::CircleShape * mercuryShape;
        sf::Vector2f velocityMercury;
        double acceleration;
        

        //buttons
        Button * buttonSol;
        Button * buttonMercury;

        //window
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
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) // Ruta de la fuente de texto
    {
    // Manejo de errores si la fuente no se pudo cargar
    }

    //buttons
    buttonSol = new Button(100,100,&font,"S",
    sf::Color::Yellow,sf::Color::Black,sf::Color::Green);

    buttonMercury = new Button(100,100,&font,"S",
    sf::Color::Yellow,sf::Color::Black,sf::Color::Green);

    //bodys maker
    solShape = new sf::CircleShape(35);
    solShape->setFillColor(sf::Color::Yellow);
    solShape->setPosition(200,200);

    mercuryShape = new sf::CircleShape(15);
    mercuryShape->setFillColor(sf::Color::Blue);
    position(0, 0);

    //window specks
    width = 800;
    width = 600; 
    height = 600;
    title = "Simulacion Sol-Mercurio";

    //window 
    window = new sf::RenderWindow(sf::VideoMode(width,height),title);
    fps = 60;
    window->setFramerateLimit(fps);
    event1 = new sf::Event();

    loop();
    std::cout << "Finished." << std::endl;

}


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