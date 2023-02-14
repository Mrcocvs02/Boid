#include "Predator.hpp"

Predator::Predator(Coordinates const& Position_, Coordinates const& Velocity_): Boid(Position_,Velocity_){movement_check=true;}

void Predator::Predator_Movement() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
    movement_check = false;
  };
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    movement_check = true;
  };
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    Position=Position + Coordinates{-5,0};
  };
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    Position=Position + Coordinates{5,0};
  };
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
  Position=Position + Coordinates{0,-5};
  };
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    Position=Position + Coordinates{0,5};
  };
}
