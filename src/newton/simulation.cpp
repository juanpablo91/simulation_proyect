#include <iostream>
#include <cmath>
#include <boost/numeric/odeint.hpp>


#include "../smfl/Sol.cpp"
#include "../smfl/Mercury.cpp"

using namespace boost::numeric::odeint;

struct Sol {
    double masa;
};

struct Mercurio {
    double masa;
    double x, y; // Posición
    double vx, vy; // Velocidad
};

// Definición de las ecuaciones de movimiento
void movimiento(const std::vector<double>& x, std::vector<double>& dxdt, double t)
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
    double Fx_sol = G * x[8].masa * x[9].masa * dx_sol / (r_sol * r_sol * r_sol);
    double Fy_sol = G * x[8].masa * x[9].masa * dy_sol / (r_sol * r_sol * r_sol);
    double Fx_mercurio = -Fx_sol;
    double Fy_mercurio = -Fy_sol;

    // Actualización de las derivadas
    dxdt[0] = vx_sol;
    dxdt[1] = vy_sol;
    dxdt[2] = Fx_sol / x[8].masa;
    dxdt[3] = Fy_sol / x[8].masa;
    dxdt[4] = vx_mercurio;
    dxdt[5] = vy_mercurio;
    dxdt[6] = Fx_mercurio / x[9].masa;
    dxdt[7] = Fy_mercurio / x[9].masa;
}

int main()
{
    const double dt = 3600.0; // Paso de tiempo (en segundos)
    const double tmax = 365.25 * 24 * 3600; // Tiempo total de la simulación (en segundos)

    std::vector<double> x(10); // Vector de variables: [x_sol, y_sol, vx_sol, vy_sol, x_mercurio, y_mercurio, vx_mercurio, vy_mercurio]

    // Condiciones iniciales
    x[0] = 0.0;  // Posición x del Sol
    x[1] = 0.0;  // Posición y del Sol
    x[2] = 0.0;  // Velocidad x del Sol
    x[3] = 0.0;  // Velocidad y del Sol

    x[4] = 0.387 * 1.496e11;  // Posición x de Mercurio (distancia en UA convertida a metros)
    x[5] = 0.0;               // Posición y de Mercurio
    x[6] = 0.0;               // Velocidad x de Mercurio
    x[7] = 47870.0;           // Velocidad y de Mercurio (en metros por segundo)

    // Definición de las masas del Sol y Mercurio
    Sol sol;
    sol.masa = 1.989e30;
    Mercurio mercurio;
    mercurio.masa = 3.285e23;

    // Asignación de los objetos Sol y Mercurio al vector x
    x[8] = sol;
    x[9] = mercurio;

    // Definición del integrador de Euler
    typedef runge_kutta4<std::vector<double>> stepper;
    integrate_const(stepper(), movimiento, x, 0.0, tmax, dt);

    // Impresión de los resultados
    std::cout << "Tiempo: " << tmax / 24 / 3600 << " días" << std::endl;
    std::cout << "Posición final de Mercurio: (" << x[4] / 1.496e11 << ", " << x[5] / 1.496e11 << ") UA" << endl;

    return 0;
}
