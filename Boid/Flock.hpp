#include <chrono>
#include <numeric>
#include <random>
#include <vector>

#include "Predator.hpp"

#ifndef FLOCK_HPP
#define FLOCK_HPP

class Flock {
  float d;
  float s;
  float a;
  float c;
  int n;
  Predator Predator_;
  std::vector<Boid> Flock_;
  std::vector<Coordinates> Obstacles;

  Boid Medium;


 public:
  Flock(float d_, float s_, float a_, float c_, int n_);

  std::vector<Boid> get_flock() const { return Flock_; };
  Predator Get_Predator() const { return Predator_; };
  void Set_Predator(Predator const& a) { Predator_ = a; };

  Boid& Get_Medium_Boid() {return Medium;};
  void Set_Medium_Boid(Boid const& a) { Medium = a; };

  std::vector<Coordinates> Get_Obstacles() const { return Obstacles; };

  Coordinates Medium_Velocity() const;
  float Sdv_Medium_Velocity() const;
  Coordinates Center_Of_Mass() const;
  float Sdv_Center_Of_Mass() const;
  float Medium_Distance() const;

  Coordinates V_Separation_i(int i) const;
  Coordinates V_Allignement_i(int i)const;
  Coordinates V_Cohesion_i(int i)const;
  Coordinates Predator_Repulsion(int i)const;
  Coordinates Obstacles_Repulsion(int i)const;

  void Rules(int i);
  void Set_Velocity(int i);

  void Predator_Simulation();
  void Simulation();
};
#endif