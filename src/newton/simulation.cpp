#include <iostream>
#include <cmath>
#include <valarray>
#include <boost/numeric/odeint.hpp>

using namespace std;
using namespace boost::numeric::odeint;

struct Sol {
    std::valarray<double> R; // Posiciones
    std::valarray<double> V; // Velocidades
    std::valarray<double> F; // Fuerzas
    const double mass = 1.989e30; // kg

    Sol() : R(2), V(2), F(2) {}
};

struct Mercury {
    std::valarray<double> R; // Posiciones
    std::valarray<double> V; // Velocidades
    std::valarray<double> F; // Fuerzas
    const double mass = 3.285e23; // kg
    const double radius = 2439.7; // km de radio

    Mercury() : R(2), V(2), F(2) {}
};

void init_system(Sol& mysol, Mercury& mymercury)
{
    mysol.R = {0, 0};   // Posicion del sol en X y Y
    mysol.V = {0, 0};   // Velocidad y del Sol en X y Y

    mymercury.R = {0.387 * 1.496e11, 0}; // Posición X y Y de Mercurio (distancia en UA convertida a metros)
    mymercury.V = {0, 47870.0};          // Velocidad X y Y de Mercurio (en metros por segundo)
}

void compute_forces(Sol& mysol, Mercury& mymercury)
{
    const double G = 6.67430e-11; // Constante de gravitación universal

    // x_mercurio          // x_sol
    double dx_sol = mymercury.R[0] - mysol.R[0];

    // y_mercurio          // y_sol
    double dy_sol = mymercury.R[1] - mysol.R[1];
    double r_sol = sqrt(dx_sol * dx_sol + dy_sol * dy_sol);

    mysol.F[0] = G * mymercury.mass * mysol.mass * dx_sol / (r_sol * r_sol * r_sol);
    mysol.F[1] = G * mymercury.mass * mysol.mass * dy_sol / (r_sol * r_sol * r_sol);

    mymercury.F[0] = -mysol.F[0]; //-Fx_sol ;
    mymercury.F[1] = -mysol.F[1]; //-Fy_sol;
}


/*// Definición de las ecuaciones de movimiento
void movimiento(const std::valarray<double>& x, std::valarray<double>& dxdt, double t,Sol &mysol,Mercury &mymercury)
{

    compute_forces(mysol, mymercury);

    // Actualización de las derivadas
    dxdt[0] = mysol.V[0];
    dxdt[1] = mysol.V[1];
    dxdt[2] = mysol.F[0] / mysol.mass;
    dxdt[3] = mysol.F[1] / mysol.mass;
    dxdt[4] = mymercury.V[0];
    dxdt[5] = mymercury.V[1];
    dxdt[6] = mymercury.F[0] / mymercury.mass;
    dxdt[7] = mymercury.F[1] / mymercury.mass;
}
*/
int main()
{
    const double dt = 3600.0;                              // Paso de tiempo (en segundos)
    const double tmax = 365.25 * 24 * 3600;                 // Tiempo total de la simulación (en segundos)

    Sol sol;
    Mercury mercury;

    // Initialize the sol and mercury 
    init_system(sol, mercury);

    // compute the initial forces
    compute_forces(sol, mercury);
    
    //print states 

    //time loopp
    //compute neew positions and velocities -integration
    //compute new forces 
    //print states

    // Definición del integrador de Euler
    typedef runge_kutta4<std::valarray<double>> stepper;
    double t = 0.0; // Tiempo inicial

    for(int i = 0; i < 2; i++){
        std::cout << sol.R[i]<<"\t"<<sol.V[i]<<"\t"<<sol.F[i]<<"\n";
    }
    return 0;
}
