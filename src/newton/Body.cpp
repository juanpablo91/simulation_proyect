#include <SFML/Graphics.hpp>
#include <valarray>

struct Body {
    std::valarray<double> R; // Posiciones
    std::valarray<double> V; // Velocidades
    std::valarray<double> F; // Fuerzas
    double mass;  // 

    Body(){
		R = {0, 0}; V = {0, 0}; F = {0, 0};
        mass = 0.0;
        
    };

    //Grafic
    sf::CircleShape * circle;
};