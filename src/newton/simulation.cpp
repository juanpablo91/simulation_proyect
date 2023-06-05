#include <iostream>
#include <cmath>
#include <valarray>
#include <boost/numeric/odeint.hpp>
#include <boost/array.hpp>

using namespace std;
using namespace boost::numeric::odeint;

typedef boost::array< double , 8 > state_type;


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


void write_lorenz( const state_type &x , const double t )
{
    std::cout << "Tiempo: " << t / 24 / 3600 << " días" << std::endl;
    std::cout << "Posición de Mercurio: (" << x[4] / 1.496e11 << ", " << x[5] / 1.496e11 << ") UA" << std::endl;
}


// Definición de las ecuaciones de movimientos
void movimiento(const state_type & x, state_type & dxdt, double t)
{
    const double G = 6.67430e-11; // Constante de gravitación universal

    // Descomposición de las variables
    double x_sol = x[0];
    double y_sol = x[1];
    double vx_sol = x[2];
    double vy_sol = x[3];
    double x_mercurio = x[4];
    double y_mercurio = x[5];
    double vx_mercurio = x[6];
    double vy_mercurio = x[7];

    // Cálculo de las fuerzas gravitacionales
    double dx_sol = x_mercurio - x_sol;
    double dy_sol = y_mercurio - y_sol;
    double r_sol = sqrt(dx_sol * dx_sol + dy_sol * dy_sol);
    double Fx_sol = G * Sol().mass * Mercury().mass * dx_sol / (r_sol * r_sol * r_sol);
    double Fy_sol = G * Sol().mass * Mercury().mass * dy_sol / (r_sol * r_sol * r_sol);
    double Fx_mercurio = -Fx_sol;
    double Fy_mercurio = -Fy_sol;

    // Actualización de las derivadas
    dxdt[0] = vx_sol;
    dxdt[1] = vy_sol;
    dxdt[2] = Fx_sol / Sol().mass;
    dxdt[3] = Fy_sol / Sol().mass;
    dxdt[4] = vx_mercurio;
    dxdt[5] = vy_mercurio;
    dxdt[6] = Fx_mercurio / Mercury().mass;
    dxdt[7] = Fy_mercurio / Mercury().mass;
}

int main()
{
    const double dt = 3600.0; // Paso de tiempo (en segundos)
    const double tmax = 365.25 * 24 * 3600; // Tiempo total de la simulación (en segundos)

    state_type x; // Vector de variables: [x_sol, y_sol, vx_sol, vy_sol, x_mercurio, y_mercurio, vx_mercurio, vy_mercurio]

    // Condiciones iniciales
    x[0] = 0.0;  // Posición x del Sol
    x[1] = 0.0;  // Posición y del Sol
    x[2] = 0.0;  // Velocidad x del Sol
    x[3] = 0.0;  // Velocidad y del Sol

    x[4] = 0.387 * 1.496e11;  // Posición x de Mercurio (distancia en UA convertida a metros)
    x[5] = 0.0;               // Posición y de Mercurio
    x[6] = 0.0;               // Velocidad x de Mercurio
    x[7] = 47870.0;           // Velocidad y de Mercurio (en metros por segundo)

    // Definición del integrador de Euler


        // Integración de las ecuaciones de movimiento
        integrate( movimiento, x , 0.0 , tmax, dt ,write_lorenz);

    return 0;
}










/* 
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

void init_system(Sol& mysol, Mercury& mymercury);
void compute_forces(Sol& mysol, Mercury& mymercury);
void print_state(Sol &mysol,Mercury &mymercury, double time);
void integration(Sol& mysol, Mercury& mymercury,double DT);


/*  
void integration(std::valarray<double>& dxdt, double t,Sol &mysol,Mercury &mymercury)
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

int main()
{
    const double dt = 3600.0; // Paso de tiempo (en segundos)
    const double tmax = 365.25 * 24 * 3600;
    double t  =0.0;// Tiempo total de la simulación (en segundos)

    Sol sol;
    Mercury mercury;

    // Initialize the sol and mercury 
    init_system(sol, mercury);

    // compute the initial forces
    compute_forces(sol, mercury);
    
    //time loopp
    print_state(sol,mercury,0.0);
    integration(sol,mercury,dt);
    //compute neew positions and velocities -integration
    //compute new forces 
    //print states
    print_state(sol,mercury,t+dt);

    // Definición del integrador de Euler


    for(int i = 0; i < 2; i++){
        std::cout << sol.R[i]<<"\t"<<sol.V[i]<<"\t"<<sol.F[i]<<"\n";
        std::cout << sol.R[i]<<"\t"<<sol.V[i]<<"\t"<<sol.F[i]<<"\n";
    }

    return 0;
}

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

void integration(Sol& mysol, Mercury& mymercury,double DT){

    std::vector<double> dxdt(8);
    // Actualización de las derivadas
    dxdt[0] = mysol.V[0];
    dxdt[1] = mysol.V[1];
    dxdt[2] = mysol.F[0] / mysol.mass;
    dxdt[3] = mysol.F[1] / mysol.mass;
    dxdt[4] = mymercury.V[0];
    dxdt[5] = mymercury.V[1];
    dxdt[6] = mymercury.F[0] / mymercury.mass;
    dxdt[7] = mymercury.F[1] / mymercury.mass;

    

};

void print_state(Sol &mysol,Mercury &mymercury, double time){

    std::cout << time << "\t" << mymercury.R[0]/ 1.496e11 << "\t" << mymercury.R[1]/ 1.496e11 << "\n"; //UA
};

*/