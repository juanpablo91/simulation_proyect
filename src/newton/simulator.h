
#pragma once
#include <map>
#include <string>

class Collider {
  std::map<std::string, double> params; // parameters to compute the forces
  public:
    Collider(const std::map<std::string, double> & PARAMS) {
      params = PARAMS;
    }
    template<class particle_array_t>
    void computeForces(particle_array_t & parray) {
      // reset forces
      for (auto & p : parray) {
        p.F = 0.0;
      }
      // individual forces

    double dx_= parray[0].R[0] - parray[1].R[0];
    double dy_= parray[0].R[1] - parray[1].R[1];

    //ax_mercurio = G * masa_sol * (x_sol - x_mercurio) / (distancia_entre_cuerpos)^3
    //ay_mercurio = G * masa_sol * (y_sol - y_mercurio) / (distancia_entre_cuerpos)^3
    double r_ = sqrt(pow(dx_, 2) + pow(dy_, 2));

    parray[1].F[0] += (params["G"] * parray[0].mass * dx_)/ ( pow(r_, 3) ); 
    parray[1].F[1] += (params["G"] * parray[0].mass * dy_) / ( pow(r_, 3) );

    }
};

class TimeIntegrator{
  double dt{0.0};

  public:
  TimeIntegrator(double DT) { dt = DT; }
  template <class particle_array_t>
  void startIntegration(particle_array_t & parray) {
        for (auto & p : parray) {
         p.V = p.V - dt*p.F / (2.0);
        }

  }
  template <class particle_array_t>
  void timeStep(particle_array_t & parray) {
        for (auto & p : parray) {
         p.V = p.V + dt *p.F;
         p.R = p.R + dt *p.V ;
        }

  }
};