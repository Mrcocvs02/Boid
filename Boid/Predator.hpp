#include "Boid.hpp"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#ifndef PREDATOR_HPP
#define PREDATOR_HPP

class Predator : public Boid {
    bool movement_check;
    public:
    Predator(Coordinates const& Position_, Coordinates const& Velocity_);
    void Predator_Movement();
    bool get_Movement_Check(){return movement_check;};
};

#endif 