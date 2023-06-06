#include <SFML/Graphics.hpp>
#include <valarray>

struct Body {
    std::valarray<double> R; // Posiciones
    std::valarray<double> V; // Velocidades
    std::valarray<double> F; // Fuerzas
    const double massMercury = 1.0; // unidad de masa mercurio
    const double massSol = 6.05e6; // 

    Body() : R(2), V(2), F(2){};

    //Grafic
    sf::CircleShape * circle;
};