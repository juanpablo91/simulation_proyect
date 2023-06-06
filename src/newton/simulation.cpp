#include <iostream>
#include <cmath>
#include <valarray>
#include <SFML/Graphics.hpp>
#include <boost/numeric/odeint.hpp>
#include <boost/array.hpp>

#include "../smfl/Body.cpp"
//#include "../smfl/CelestialSystem.cpp"

using namespace std;
using namespace boost::numeric::odeint;

typedef boost::array< double , 8 > state_type;

void write_sim( const state_type &x , double t )
{
    std::cout << "Tiempo: " << t / 24 / 3600 << " días" << std::endl;
    std::cout << "Posición de Mercurio: (" << x[4]  << ", " << x[5]  << ") UA" << std::endl;
    //print_sim(x);
}


// Definición de las ecuaciones de movimientos
void sim(const state_type & x, state_type & dxdt, double t)
{   
    const double G =6.67430e-11 // Constante de gravitación universal
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
    double Fx_sol = G * Body().massSol * Body().massMercury * dx_sol / (r_sol * r_sol * r_sol); 
    double Fy_sol = G * Body().massSol * Body().massMercury * dy_sol / (r_sol * r_sol * r_sol);
    double Fx_mercury = -Fx_sol;
    double Fy_mercury= -Fy_sol;

    // Actualización de las derivadas
    dxdt[0] = vx_sol;
    dxdt[1] = vy_sol;
    dxdt[2] = Fx_sol / Body().massSol;
    dxdt[3] = Fy_sol / Body().massSol;
    dxdt[4] = vx_mercury;
    dxdt[5] = vy_mercury;
    dxdt[6] = Fx_mercury / Body().massMercury;
    dxdt[7] = Fy_mercury / Body().massMercury;


}

int main()
{
    const double dt = 1.0; // Paso de tiempo (en segundos)
    const double tmax = 365.35; // Tiempo total de la simulación (en segundos)

    state_type x; // Vector de variables: [x_sol, y_sol, vx_sol, vy_sol, x_mercurio, y_mercurio, vx_mercurio, vy_mercurio]

    // Condiciones iniciales
    x[0] = 0.0;  // Posición x del Sol
    x[1] = 0.0;  // Posición y del Sol
    x[2] = 0.0;  // Velocidad x del Sol
    x[3] = 0.0;  // Velocidad y del Sol

    x[4] = 0.387;  // Posición x de Mercurio (distancia en UA convertida a metros)
    x[5] = 0.0;               // Posición y de Mercurio
    x[6] = 0.0;               // Velocidad x de Mercurio
    x[7] = 47870.0;           // Velocidad y de Mercurio (en metros por segundo)

    //CelestialSystem  * system;
    //system = new CelestialSystem();

    // Definir la escala de conversión de coordenadas (1 pixel = 1000 km)
    //const double scale = 1000.0;

    // Obtener las coordenadas de posición de Mercurio en la simulación
    //double x_mercury_sim = x[4];
    //double y_mercury_sim = x[5];

    // Convertir las coordenadas de posición de la simulación a las coordenadas de la ventana
    //double X_mercury_window = x_mercury_sim/ scale;
    //double Y_mercury_window = y_mercury_sim / scale;
    
    // Integración de las ecuaciones de movimiento
    typedef runge_kutta4<state_type> stepper;
    for (double t = 0.0; t <= tmax; t += dt) {

        // Impresión de los resultados en cada paso de tiempo
        write_sim(x,t);

        //system->position(x[4],x[5]);

        // Integración de las ecuaciones de movimiento
        integrate_const(stepper(), sim, x, t, t + dt, dt);
    }



    return 0;
}