#pragma once

#include <SFML/Graphics.hpp>
#include <valarray>

struct Body {

    std::valarray<double> R; // Posiciones
    std::valarray<double> V; // Velocidades
    std::valarray<double> F; // Fuerzas
    double mass;  // 

    //Grafic
    sf::CircleShape * circle;
    sf::Vector2f velocity;

    Body(){
		R = {0, 0}; V = {0, 0}; F = {0, 0};
        mass = 0.0;

        //grafic
        velocity.x = 2;
        velocity.y = 1;
    
    };

    

    void update(double time, double x, double y) {
        circle->setPosition(circle->getPosition().x + velocity.x * time, circle->getPosition().y + velocity.y * time);
    };


 
};