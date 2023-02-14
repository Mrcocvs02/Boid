#include "Coordinates.hpp"

#ifndef BOID_HPP
#define BOID_HPP

class Boid {
  protected:
  Coordinates Position;
  Coordinates Velocity;

 public:
  Boid(Coordinates const& P, Coordinates const& V);

  void Set_Position(Coordinates const& P);
   Coordinates Get_Position() const;
   void Set_Velocity(Coordinates const& V);
   Coordinates Get_Velocity()const;

  void Wall_Hit();
  
};

#endif