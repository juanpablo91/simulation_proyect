#pragma once
#include <iostream>
#include <cmath>

#include <boost/numeric/odeint.hpp>
#include <boost/array.hpp>
#include <fstream>

#include "Body.cpp"

using namespace std;
using namespace boost::numeric::odeint;

typedef boost::array< double , 8 > state_type;

void write_sim( const state_type &x , double t )
{
    std::cout << "Tiempo: " << t / 24 / 3600 << " días" << std::endl;
    std::cout << "Posición de Mercurio: (" << x[4] / 1.496e11 << ", " << x[5]  / 1.496e11<< ") UA" << std::endl;
    //print_sim(x);
}


// Definición de las ecuaciones de movimientos
void sim(const state_type & x, state_type & dxdt, double t)
{   
    const double G =6.67430e-11;
    double massSol = 1.989e30;
    double massMercury= 3.285e23;
    
    const double periodoMercurio = 87.969 * 24 * 3600; // Periodo orbital de Mercurio (en segundos)
    const double semiejeMayorMercurio = 0.387 * 1.496e11; // Semieje mayor de la órbita de Mercurio (en metros)


    // Constante de gravitación universal
   //( 6.67430e-11) * 1.989e30 * pow(1.0, 3) / Body().massSol
    // Descomposición de las variables
    double x_sol = x[0];
    double y_sol = x[1];
    double vx_sol = x[2];
    double vy_sol = x[3];
    double x_mercury = x[4];
    double y_mercury = x[5];
    double vx_mercury = x[6];
    double vy_mercury = x[7];

    // Cálculo de las fuerzas gravitacionales
    double dx_sol = x_mercury- x_sol;  
    double dy_sol = y_mercury - y_sol;
    double r_sol = sqrt(dx_sol * dx_sol + dy_sol * dy_sol);
    double Fx_sol = G * massSol * massMercury * dx_sol / (r_sol * r_sol * r_sol); 
    double Fy_sol = G * massSol * massMercury * dy_sol / (r_sol * r_sol * r_sol);
    double Fx_mercury = -Fx_sol;
    double Fy_mercury= -Fy_sol;

    // Actualización de las derivadas
    dxdt[0] = vx_sol;
    dxdt[1] = vy_sol;
    dxdt[2] = Fx_sol / massSol;
    dxdt[3] = Fy_sol / massSol;
    dxdt[4] = vx_mercury;
    dxdt[5] = vy_mercury;
    dxdt[6] = Fx_mercury / massMercury;
    dxdt[7] = Fy_mercury / massMercury;

 }

 void compute(std::vector<Body> &body){

    std::ofstream fout("data.txt"); 
    std::cout <<"Corriendo Simulacioon..." << "\n";

    const double dt = 3600.0; // Paso de tiempo (en segundos)
    const double tmax = 365.25 * 24 * dt; // Tiempo total de la simulación (en segundos)

    state_type x; // Vector de variables: [x_sol, y_sol, vx_sol, vy_sol, x_mercurio, y_mercurio, vx_mercurio, vy_mercurio]

    // Condiciones iniciales
    x[0] = 0.0;  // Posición x del Sol
    x[1] = 0.0;  // Posición y del Sol
    x[2] = 0.0;  // Velocidad x del Sol
    x[3] = 0.0;  // Velocidad y del Sol

    x[4] = 0.387 * 1.496e11;  // Posición x de Mercurio (distancia en UA convertida a metros)
    x[5] = 0.0;               // Posición y de Mercurio
    x[6] = 0.0;               // Velocidad x de Mercurio
    x[7] = 47870.0;        // Velocidad y de Mercurio (en metros por segundo)

    // Integración de las ecuaciones de movimiento
    typedef runge_kutta4<state_type> stepper;
    for (double t = 0.0; t <= tmax; t += dt) {

        // Impresión de los resultados en cada paso de tiempo
        write_sim(x,t);

        //system->position(x[4],x[5]);

        // Integración de las ecuaciones de movimiento
        integrate_const(stepper(), sim, x, t, t + dt, dt);

        fout << t/ 24 / 3600 << "\t" << x[4]/ 1.496e11 << " \t" << x[5]/ 1.496e11 << "\n ";
    }

    std::cout << "Simulacion terminada..." << "\n";
 }



