#include <cassert>
#include <cmath>
#include <iostream>

#ifndef VETTORE_HPP
#define VETTORE_HPP

class Coordinates {
  float x;
  float y;

 public:
  Coordinates(float x_, float y_) : x{x_}, y{y_} {}

  float Get_x() const;
  void Set_x(float const x_);
  float Get_y() const;
  void Set_y(float const y_);

  Coordinates operator+(Coordinates const& b) const;
  Coordinates operator-(Coordinates const& b) const;
  Coordinates operator*(float const b) const;
  Coordinates operator/(float const b) const;
  double Norm() const;
  void Print() const;
};

float Scalar_Product(Coordinates const& a, Coordinates const& b);
float Angle(Coordinates const& a, Coordinates const& b);

#endif
