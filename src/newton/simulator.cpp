

#include "Body.h"
#include "simulator.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <map>

void init_system(std::vector<Body> &bodies);
void print_state(std::vector<Body> &bodies, double time);

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