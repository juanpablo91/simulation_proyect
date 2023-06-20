
#include <iostream>
#include <fstream>

#include "Button.cpp"
#include "../newton/Body.h"
#include "../newton/simulator.h"
#include "../newton/simulator.cpp"

class CelestialSystem
{
    private:

        //bodyies
        Body sol;
        Body mercury;

        //buttons
        Button * buttonSol;
        Button * buttonMercury;

        //clock
        sf::Clock * clock;
        sf::Time * time;
        sf::Time * DT;

        //window
        sf::RenderWindow * window;
        int width;
        int height;
        std::string title;
        sf::Event * event1;
        int fps;    

    
    public:
        //window functions
        CelestialSystem(std::map<std::string, double> params,std::vector<Body> &bodiess);
        void loop(std::map<std::string, double> params,std::vector<Body> &bodies);
        void processEvent();
        void _draw(std::map<std::string, double> params,std::vector<Body> &bodies,sf::VertexArray orbita,int &nsteps, int &tsteps);

        //use functions

        //void computeSystem(std::map<std::string, double> params,std::vector<Body> &bodies);
        void render(sf::RenderTarget * target);

};

CelestialSystem::CelestialSystem(std::map<std::string, double> params,std::vector<Body> &bodies)
{   
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) // Ruta de la fuente de texto
    {
    // Manejo de errores si la fuente no se pudo cargar
    }

    //buttons
    buttonSol = new Button(150,30,&font,"S",
    sf::Color::Yellow,sf::Color::Black,sf::Color::Green);

    buttonMercury = new Button(30,30,&font,"S",
    sf::Color::Cyan,sf::Color::Black,sf::Color::Green);

    //bodys maker
    sol = bodies[0];
    mercury = bodies[1];

    sol.circle = new sf::CircleShape(35);
    sol.circle->setPosition(400,400);
    sol.circle->setFillColor(sf::Color::Yellow);

    mercury.circle = new sf::CircleShape(15);
    mercury.circle->setPosition(300,300);
    mercury.circle->setFillColor(sf::Color::Cyan);

    //clock
    clock = new sf::Clock;
    time = new sf::Time;
    DT = new sf::Time;
    
    //data



    //window specks
    width = 800;
    height = 800;
    title = "Simulacion Sol-Mercurio";

    //window 
    window = new sf::RenderWindow(sf::VideoMode(width,height),title);
    fps = 60;
    window->setFramerateLimit(fps);
    event1 = new sf::Event();
    //loadData();
    loop(params,bodies);

}


void CelestialSystem::loop(std::map<std::string, double> params,std::vector<Body> &bodies)
{
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

    sf::VertexArray orbita(sf::LineStrip); // Representa la órbita de Mercurio
    orbita.setPrimitiveType(sf::LineStrip);
    orbita.append(sf::Vertex(sf::Vector2f(300, 300), sf::Color::White)); // Punto inicial de la órbita

	// Time loop
    int nsteps = std::lrint((params["TF"] - params["T0"]) / params["DT"]);
    int tsteps = 1;


    if(window->isOpen()){
        std::cout << "Abriendo Ventana-SIMULACION Iniciando..." << std::endl;
    }
    while (window->isOpen())
    {
         // Actualizar órbita
        orbita.append(sf::Vertex(sf::Vector2f(mercury.circle->getPosition().x + (1.5 *  (bodies[1].R[0]/ 1.496e11)) , mercury.circle->getPosition().y + (1.5 *  (bodies[1].R[1]/ 1.496e11))), sf::Color::White));
        processEvent();        
        if(tsteps < nsteps){

            double time = params["T0"] + tsteps * params["DT"];
		    integrator.timeStep(bodies);
		    collider.computeForces(bodies);

		    print_state(bodies, time);

		    fout << time/ 24 / 3600 << "\t" << bodies[1].R[0]/ 1.496e11 
                << "\t" << bodies[1].R[1]/ 1.496e11 << "\t" <<bodies[1].V[0]<<"\t" <<bodies[1].V[1] <<"\n ";
            tsteps +=1;
            std::cout << "tstepst: "<< tsteps<<std::endl;

        }

        
        _draw(params,bodies,orbita,tsteps,nsteps);

        *time = clock->getElapsedTime();
        std::cout << "SIMULACION Corriendo... " << time->asSeconds() << " S"<< std::endl;
        
    }
}

void CelestialSystem::processEvent(){
    while (window->pollEvent(*event1))
    {   
        switch (event1->type)
        {   
        case sf::Event::Closed:
            window->close();
            std::cout << "Ventana Cerrada-SIMULACION FINALIZADA..." << std::endl;
            exit(1);
            break;
    
        default:
            break;
        }
 
    }

}

void CelestialSystem::_draw(std::map<std::string, double> params,std::vector<Body> &bodies,sf::VertexArray orbita,int &tsteps, int &nsteps)
{   
    window->clear();
    
    if(tsteps < nsteps){
        window->draw(orbita);
        mercury.circle->setPosition(mercury.circle->getPosition().x + (2.0 *  (bodies[1].R[0]/ 1.496e11)), mercury.circle->getPosition().y + (2.0*  (bodies[1].R[1]/ 1.496e11)));
    }

    window->draw(*sol.circle);//Dibujar el Sol
    window->draw(*mercury.circle);//Dibujar de mercurio
    buttonSol->drawto(window);
    buttonMercury->drawto(window);
    window->display();
}
void CelestialSystem::render(sf::RenderTarget * target){

    this->buttonSol->render(target);

};


//lanzar la ventama
//inicializan todos lo valores.
//empieza (simulacion)  a paso
// se acaba la simulacion y obtengo los datos