#include "Flock.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

class Game {
 private:
  Flock Flock_;
  const int Display_Height;
  const int Display_Width;

  sf::CircleShape Boid_i;
  sf::CircleShape Predator_Shape;
  sf::CircleShape Flock_Center;
  sf::CircleShape Obstacle_i;
  sf::RectangleShape Data;
  sf::RectangleShape Sdv_Flock_Velocity;

  const int FPS;

  bool Play_Button;

  const float Data_Height;
  const float Data_Width;

 public:
  Game(float d, float s, float a, float c, int n);
  void Set_Immages();
  float Angle(Coordinates const& v);
  void Close_Window(sf::RenderWindow* window);
  void Run(sf::RenderWindow* window);

  void Play_button();
  void Draw(sf::RenderWindow* window);
};

#endif
