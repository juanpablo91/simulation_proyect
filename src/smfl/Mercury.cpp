#include <valarray>
#include <SFML/Graphics.hpp>

struct Mercury {
    std::valarray<double> R,V,F; //R-> positions, V-> Velocities, F->Forces
    const double mass = 3.285e23; ////kg
    const double radius = 2439.7; //km radius

    Mercury():R(2),V(2),F(2){}

    //graficos
    sf::Vector2f velocity;
    sf::CircleShape * circle; // Velocidad
};
