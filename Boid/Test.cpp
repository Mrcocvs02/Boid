#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Flock.hpp"
#include "doctest.h"

Coordinates nul{0.f, 0.f};


  TEST_CASE("testing Coordinates.cpp") {

    SUBCASE("testing Coordinates::Get_x()") {
    Coordinates a{3.f, 0.f};
    CHECK(a.Get_x() == 3.f);
  }
  
   SUBCASE("testing Coordinates::Get_y()") {
    Coordinates a{0.f, 4.f};
    CHECK(a.Get_y() == 4.f);
  }

   SUBCASE("testing Coordinates::Set_x()") {
    Coordinates a{0.f, 0.f};
    a.Set_x(2.f);
    CHECK(a.Get_x() == 2.f);
    CHECK(a.Get_y() == 0.f);
  }

    SUBCASE("testing Coordinates::Set_y()") {
    Coordinates a{0.f, 0.f};
    a.Set_y(2.f);
    CHECK(a.Get_x() == 0.f);
     CHECK(a.Get_y() == 2.f);
   }

  SUBCASE("testing Coordinates::operator+()") {
    Coordinates a{2.f, 0.f};
    Coordinates b{-4.f, 10.f};
    Coordinates res_1 = a + b;
    CHECK(res_1.Get_x() == -2.f);
    CHECK(res_1.Get_y() == 10.f);
    Coordinates c{2.6f, -9.2f};
    Coordinates res_2 = b + c;
    CHECK(res_2.Get_x() == doctest::Approx(-1.4f));
    CHECK(res_2.Get_y() == doctest::Approx(0.8f));
    Coordinates res_3 = a + b + c;
    CHECK(res_3.Get_x() == doctest::Approx(0.6f));
    CHECK(res_3.Get_y() == doctest::Approx(0.8f));
  }

  SUBCASE("testing Coordinates::operator-()") {
    Coordinates a{2.f, 1.f};
    Coordinates b{5.f, 6.f};
    Coordinates res_1 = a - b;
    CHECK(res_1.Get_x() == -3.f);
    CHECK(res_1.Get_y() == -5.f);
    Coordinates c{2.3f, 7.1f};
    Coordinates res_2 = b - c;
    CHECK(res_2.Get_x() == doctest::Approx(2.7f));
    CHECK(res_2.Get_y() == doctest::Approx(-1.1f));
    Coordinates res_3 = a - b - c;
    CHECK(res_3.Get_x() == doctest::Approx(-5.3f));
    CHECK(res_3.Get_y() == doctest::Approx(-12.1f));
  }

  SUBCASE("testing Coordinates::operator*()") {
    Coordinates a{2.f, 3.f};
    Coordinates res_1 = a * 3.f;
    CHECK(res_1.Get_x() == 6.f);
    CHECK(res_1.Get_y() == 9.f);
    Coordinates b{1.2f, -5.6f};
    Coordinates res_2 = b * 2.6;
    CHECK(res_2.Get_x() == doctest::Approx(3.12f));
    CHECK(res_2.Get_y() == doctest::Approx(-14.56f));
    Coordinates res_3 = nul * (4.6f);
    CHECK(res_3.Get_x() == 0.f);
    CHECK(res_3.Get_y() == 0.f);
    Coordinates res_4 = b * 0.f;
    CHECK(res_4.Get_x() == 0.f);
    CHECK(res_4.Get_y() == 0.f);
  }

  SUBCASE("testing Coordinates::operator/()") {
    Coordinates a{1.f, 6.f};
    Coordinates res_1 = a / 2.f;
    CHECK(res_1.Get_x() == 0.5f);
    CHECK(res_1.Get_y() == 3.f);
    Coordinates b{2.4f, 5.1f};
    Coordinates res_2 = b / 2.7;
    CHECK(res_2.Get_x() == doctest::Approx(0.8889f));
    CHECK(res_2.Get_y() == doctest::Approx(1.8889f));
    Coordinates res_3 = nul / (4.7f);
    CHECK(res_3.Get_x() == 0.f);
    CHECK(res_3.Get_y() == 0.f);
  }

  SUBCASE("testing Coordinates::Norm()") {
    Coordinates a{0.f, 0.f};
    CHECK(a.Norm() == 0.f);
    Coordinates b{10.f, -2.f};
    CHECK(b.Norm() == doctest::Approx(10.198f));
    Coordinates c{13.2f, 0.f};
    CHECK(c.Norm() == doctest::Approx(13.2f));
  }

  SUBCASE("testing Scalar_Product()") {
    Coordinates a{0.f, 0.f};
    Coordinates b{1.f, 2.f};
    CHECK(Scalar_Product(a, b) == 0.f);
    Coordinates c{1.f, 1.f};
    Coordinates d{1.f, -1.f};
    CHECK(Scalar_Product(c, d) == 0.f);
    Coordinates e{3.56f, -2.3f};
    Coordinates f{1.11f, 76.57f};
    CHECK(Scalar_Product(e, f) == doctest::Approx(-172.159f));
    CHECK(Scalar_Product(f, e) == doctest::Approx(-172.159f));
  }
}


TEST_CASE("testing Boid.cpp"){
  Coordinates a{2.f,2.f};
  Coordinates b{10.f,10.f};
  Boid Boid_1{a,b};
  
  SUBCASE("testing Boid::Get_Position()"){
    CHECK(Boid_1.Get_Position().Get_x() == 2.f);
    CHECK(Boid_1.Get_Position().Get_y() == 2.f);
  }

  
  SUBCASE("testing Boid::Get_Velocity()"){
    CHECK(Boid_1.Get_Velocity().Get_x() == 10.f);
    CHECK(Boid_1.Get_Velocity().Get_y() == 10.f);
  }


  SUBCASE("testing Boid::Set_Position()"){
    Coordinates c{3.f,3.f};
    Boid_1.Set_Position(c);
    CHECK(Boid_1.Get_Position().Get_x() == 3.f);
    CHECK(Boid_1.Get_Position().Get_y() == 3.f);
  }

  SUBCASE("testing Boid::Set_Velocity()"){
     Coordinates c{4.f,4.f};
    Boid_1.Set_Position(c);
    CHECK(Boid_1.Get_Position().Get_x() == 4.f);
    CHECK(Boid_1.Get_Position().Get_y() == 4.f);
  }

   SUBCASE("testing Boid::Wall_Hit()") {
    Coordinates c{3.f,3.f};
    Coordinates d{1178.f,626.f};
    Coordinates f{26.f,26.f};
    Boid_1.Set_Position(c);
    Boid_1.Wall_Hit();
    CHECK(
    Boid_1.Get_Velocity().Get_x() == -12.f);
    Boid_1.Set_Position(d);
    Boid_1.Wall_Hit();
    CHECK(
    Boid_1.Get_Velocity().Get_x() == 14.4f);
    Boid_1.Set_Position(f);
    Boid_1.Wall_Hit();
    CHECK(
    Boid_1.Get_Velocity().Get_x() == 14.4f); 
  }
}

TEST_CASE("testing Flock.cpp") {
   Flock Flock_1{10.f, 0.5f, 0.025f, 0.01f, 2};
 
  SUBCASE("testing Flock::Center_Of_Mass()") {
   Coordinates res_1 = Flock_1.Center_Of_Mass();
   CHECK(res_1.Get_x() < 1200);
   CHECK(res_1.Get_y() < 650);
  }

  SUBCASE("testing Flock::Medium_Velocity()") {
    Coordinates res_1 = Flock_1.Medium_Velocity();
    CHECK(res_1.Get_x() < 150);
    CHECK(res_1.Get_y() < 150);
  }


  SUBCASE("testing Flock::Sdv_Center_Of_Mass()") {
    float sdv = Flock_1.Sdv_Center_Of_Mass();
    CHECK(sdv < 1000);
  }


  SUBCASE("testing Flock::Sdv_Medium_Velocity()") {
  float sdv = Flock_1.Sdv_Medium_Velocity();
    CHECK(sdv < 40);
  }

  SUBCASE("testing Flock::V_Separation_i()") {
  Coordinates res_1 = Flock_1.V_Separation_i(0);
  CHECK(res_1.Get_x() < 500);
  CHECK(res_1.Get_y() < 500);
   Coordinates res_2 = Flock_1.V_Separation_i(1);
  CHECK(res_2.Get_x() < 500);
  CHECK(res_2.Get_y() < 500);
  }

  SUBCASE("testing Flock::V_Allignement_i") {
   Coordinates res_1 = Flock_1.V_Allignement_i(0);
  CHECK(res_1.Get_x() < 500);
  CHECK(res_1.Get_y() < 500);
   Coordinates res_2 = Flock_1.V_Allignement_i(1);
  CHECK(res_2.Get_x() < 500);
  CHECK(res_2.Get_y() < 500);
  }

  SUBCASE("testing Flock::V_Cohesion_i()") {
   Coordinates res_1 = Flock_1.V_Cohesion_i(0);
  CHECK(res_1.Get_x() < 500);
  CHECK(res_1.Get_y() < 500);
   Coordinates res_2 = Flock_1.V_Cohesion_i(1);
  CHECK(res_2.Get_x() < 500);
  CHECK(res_2.Get_y() < 500);

  } 

 SUBCASE("testing Flock::Predator_Repulsion()") {
   Coordinates res_1 = Flock_1.Predator_Repulsion(0);
   CHECK(res_1.Get_x() < 1000);
   CHECK(res_1.Get_y() < 1000);
    Coordinates res_2 = Flock_1.Predator_Repulsion(1);
   CHECK(res_2.Get_x() < 1000);
   CHECK(res_2.Get_y() < 1000);
  }

 SUBCASE("testing Flock::Obstacles_Repulsion()"){
   Coordinates res_1 = Flock_1.Obstacles_Repulsion(0);
   CHECK(res_1.Get_x() < 1000);
   CHECK(res_1.Get_y() < 1000);
    Coordinates res_2 = Flock_1.Obstacles_Repulsion(1);
   CHECK(res_2.Get_x() < 1000);
   CHECK(res_2.Get_y() < 1000);
 }
 
}
