//Este es el principal archivo, donde se uniran las tres partes fundamentales del progra
#include <SFML/Graphics.hpp>
#include "./smfl/CelestialSystem.cpp"
#include <string>
#include <valarray>

int main(int argc,char **argv){


    CelestialSystem * system1;

    system1 = new CelestialSystem({9.0,1.0},5.0);

    return 0;
}
