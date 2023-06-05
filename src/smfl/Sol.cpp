#include <SFML/Graphics.hpp>
#include <valarray>

struct Sol{
    std::valarray<double> R,V,F; //R-> positions, V-> Velocities, F->Forces
    const double mass = 1.989e30;//kg 

    Sol():R(2),V(2),F(2) {}
    
    //Grafic
    sf::CircleShape * circle;
};
