
//all configuration of window here 
#include <SFML/Graphics.hpp>
#include "./CelestialSystem.cpp"

int main(int argc,char **argv){

    // Simulacion
    std::map<std::string, double> params;
    params["G"] = 6.67430e-11;
	params["DT"] = 3600.0;
	params["T0"] = 0.0;
	params["TF"] = (365.25 * 24 * 3600);
    params["nsteps"] = std::lrint((params["TF"] - params["T0"]) / params["DT"]);
    params["tstep "]=1; 

	const int N = 2;
	std::vector<Body> bodies(N);

    //creamos la ventana que contiene al sistema celeste
    CelestialSystem * system1;
    system1 = new CelestialSystem(params, bodies);


    return 0;
}

