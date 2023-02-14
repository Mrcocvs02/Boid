#include "Boid.hpp"

Boid::Boid(Coordinates const& P, Coordinates const& V)
    : Position{P}, Velocity{V} {}

void Boid::Set_Position(Coordinates const& P) { Position = P; }
Coordinates Boid::Get_Position() const { return Position; }
void Boid::Set_Velocity(Coordinates const& V) { Velocity = V; }
Coordinates Boid::Get_Velocity() const { return Velocity; }

void Boid::Wall_Hit() {
  if ((Position.Get_x() <= 25) || (Position.Get_x() >= 1175)) {
    Velocity.Set_x(-1.2 * Velocity.Get_x());
  }
  if ((Position.Get_y() <= 25) || (Position.Get_y() >= 625)) {
    Velocity.Set_y(-1.2 * Velocity.Get_y());
  }
}
