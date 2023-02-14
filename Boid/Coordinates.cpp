#include "Coordinates.hpp"

float Coordinates::Get_x() const { return x; };
float Coordinates::Get_y() const { return y; };
void Coordinates::Set_x(float const x_) { x = x_; };
void Coordinates::Set_y(float const y_) { y = y_; };
Coordinates Coordinates::operator+(Coordinates const& b) const {
  return {(x + b.Get_x()), (y + b.Get_y())};
};
Coordinates Coordinates::operator-(Coordinates const& b) const {
  return {(x - b.Get_x()), (y - b.Get_y())};
};
Coordinates Coordinates::operator*(float const b) const {
  return {(x * b), (y * b)};
};
Coordinates Coordinates::operator/(float const b) const {
  assert(b != 0);
  return {x / b, y / b};
};
double Coordinates::Norm() const { return (std::sqrt(x * x + y * y)); };
void Coordinates::Print() const {
  std::cout << "(" << x << ", " << y << ")" << '\n';
};

float Scalar_Product(Coordinates const& a, Coordinates const& b) {
  return a.Get_x() * b.Get_x() + a.Get_y() * b.Get_y();
};
float Angle(Coordinates const& a, Coordinates const& b) {
  return acos(Scalar_Product(a, b) / (a.Norm() * b.Norm()));
};
