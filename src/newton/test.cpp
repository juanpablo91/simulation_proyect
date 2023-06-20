#include <SFML/Graphics.hpp>

#include "Body.h"
#include "simulator.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <map>

void init_system(std::vector<Body> &bodies)
{
    //Sol
	bodies[0].mass = 1.989e30; //masa del sol

    //Mercurio
    bodies[1].mass = 3.285e23; //masa de mercurio
    bodies[1].R[0] = 0.387 * 1.496e11; //posiicion en y
    bodies[1].V[1] = 47870.0; //velocidad en y

}

void print_state(std::vector<Body> &bodies, double time)
{
	std::cout << time / 24 / 3600  << " ";

		std::cout << bodies[1].R[0] / 1.496e11 << " \t" << bodies[1].R[1] / 1.496e11<< " \t";

	std::cout << std::endl;
}




int main()
{

    std::map<std::string, double> params;
    params["G"] = 6.67430e-11;
	params["DT"] = 3600.0;
	params["T0"] = 0.0;
	params["TF"] = (365.25 * 24 * 3600);

	const int N = 2;
	std::vector<Body> bodies(N);
	std::ofstream fout("data.txt"); 

	TimeIntegrator integrator(params["DT"]);

	Collider collider(params);

	// Initialize particles: R(0), V(0)
	init_system(bodies);
	// Compute initial forces: F(0)
	collider.computeForces(bodies);

	// start integration
	integrator.startIntegration(bodies);

	// print state
	print_state(bodies, params["T0"]);

	// Time loop
	int nsteps = std::lrint((params["TF"] - params["T0"]) / params["DT"]);
    int tstep = 1;


    sf::RenderWindow window(sf::VideoMode(800, 800), "Simulación del sistema Sol-Mercurio");

    // Definir los cuerpos
    sf::CircleShape sol(20.f); // Representa el Sol
    sol.setFillColor(sf::Color::Yellow);
    sol.setPosition(400, 400);


    // Definir la escala
    double escala = 100.0; // Escala para ajustar las posiciones al tamaño de la ventana

    sf::VertexArray orbita(sf::LineStrip); // Representa la órbita de Mercurio
    orbita.setPrimitiveType(sf::LineStrip);
    orbita.append(sf::Vertex(sf::Vector2f(300, 300), sf::Color::White)); // Punto inicial de la órbita

    sf::CircleShape mercurio(10.f); // Representa a Mercurio
    mercurio.setFillColor(sf::Color::Cyan);
    mercurio.setPosition(300, 300);


    // Bucle principal
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(tstep < nsteps){

            double time = params["T0"] + tstep*params["DT"];
		    integrator.timeStep(bodies);
		    collider.computeForces(bodies);

		    print_state(bodies, time);

		    fout << time/ 24 / 3600 << "\t" << bodies[1].R[0]/ 1.496e11 << "\t" << bodies[1].R[1]/ 1.496e11 <<"\n ";
            tstep += 1;

        }

        // Actualizar órbita
        orbita.append(sf::Vertex(sf::Vector2f(mercurio.getPosition().x + (2.0 *  (bodies[1].R[0]/ 1.496e11)) , mercurio.getPosition().y + (2.0*  (bodies[1].R[1]/ 1.496e11))), sf::Color::White));

        // Actualizar posiciones
        // Aquí debes aplicar el método de Leapfrog o cualquier otro método de actualización de posiciones

        // Borrar ventana
        window.clear();
        window.draw(orbita);

        mercurio.setPosition(mercurio.getPosition().x + (2.0 *  (bodies[1].R[0]/ 1.496e11)), mercurio.getPosition().y + (2.0*  (bodies[1].R[1]/ 1.496e11)));
        std::cout<< "x:"<< mercurio.getPosition().x + (2.0 *  (bodies[1].R[0]/ 1.496e11)) << "\t" <<  "y: "<< mercurio.getPosition().y + (2.0 *  (bodies[1].R[1]/ 1.496e11)) <<"\n ";
        // Dibujar cuerpos
        window.draw(sol);

        window.draw(mercurio);

        // Actualizar ventana
        window.display();
    }

    return 0;
}







