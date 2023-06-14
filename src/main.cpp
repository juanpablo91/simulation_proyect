//Este es el principal archivo, donde se uniran las tres partes fundamentales del progra
#include <SFML/Graphics.hpp>
#include "./newton/simulator.cpp"
#include <string>
#include <valarray>

int main(int argc,char **argv){

    const int N = 2;
    std::vector<Body> body(N);
    compute(body);

    return 0;
}
