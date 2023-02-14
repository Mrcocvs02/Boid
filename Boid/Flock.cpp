#include "Flock.hpp"
#include <cmath>
#include <numeric>

Flock::Flock(float d_, float s_, float a_, float c_, int n_)
    : d{d_},
      s{s_},
      a{a_},
      c{c_},
      n{n_},
      Predator_{{(static_cast<float>(rand() % 30000 + 45000)) / 100,
                 (static_cast<float>(rand() % 15000 + 20000)) / 100},
                {static_cast<float>(rand() % 20 + 5),
                 static_cast<float>(rand() % 20 + 5)}},
      Medium{Center_Of_Mass(), Medium_Velocity()} {
  for (int i = 0; i < n; i++) {
    std::random_device rd;
    std::mt19937 random_generator(rd());
    std::normal_distribution<float> position_x(600, 100);
    std::normal_distribution<float> position_y(300, 75);
    float p_x = position_x(random_generator);
    float p_y = position_y(random_generator);
    Coordinates p_{p_x, p_y};

    std::normal_distribution<float> velocity(110., 60.);
    std::uniform_int_distribution<int> sign_x(0, 1);
    float v_x = velocity(random_generator) *
                (static_cast<float>(sign_x(random_generator)) - 0.5);
    float v_y = velocity(random_generator) *
                (static_cast<float>(sign_x(random_generator)) - 0.5);
    Coordinates v_{v_x, v_y};
    Boid boid_n(p_, v_);
    Flock_.push_back(boid_n);
  }
  while (Obstacles.size() < 10) {
    Obstacles.push_back({(static_cast<float>(rand() % 80000)) / 100 + 200,
                         (static_cast<float>(rand() % 25000)) / 100 + 200});
  }
}

Coordinates Flock::Medium_Velocity() const {
  Coordinates res{0, 0};

  auto Mean = [&](Coordinates sum, Boid next) {
    return (sum + next.Get_Velocity() / n);
  };

  res = std::accumulate(Flock_.begin(), Flock_.end(), res, Mean);

  return (res);
}

float Flock::Sdv_Medium_Velocity() const {
  double res = 0;

  auto Sdv = [&](double sum, Boid next) {
    return (sum + (next.Get_Velocity() - Medium.Get_Velocity()).Norm());
  };

  res = std::accumulate(Flock_.begin(), Flock_.end(), res, Sdv);

  return (sqrt(res / n));
}

Coordinates Flock::Center_Of_Mass() const {
  Coordinates res{0, 0};

  auto Mean = [&](Coordinates sum, Boid next) {
    return (sum + next.Get_Position() / n);
  };

  res = std::accumulate(Flock_.begin(), Flock_.end(), res, Mean);

  return (res);
}

float Flock::Sdv_Center_Of_Mass() const {
  double res = 0;

  auto Sdv = [&](double sum, Boid next) {
    return (sum + (next.Get_Position() - Medium.Get_Position()).Norm());
  };

  res = std::accumulate(Flock_.begin(), Flock_.end(), res, Sdv);
  return (res / n);
}

float Flock::Medium_Distance() const {
  std::vector<float> distances;
  int n_distances = 1;
  for (int i = 0; i < static_cast<int>(Flock_.size()) - 1; i++) {
    for ( int j = i + 1; j < static_cast<int>(Flock_.size());
         j++) {
      distances.push_back(
          (Flock_[j].Get_Position() - Flock_[i].Get_Position()).Norm());
    }
    n_distances += i;
  }
  return std::accumulate(distances.begin(), distances.end(), 0.f) / n_distances;
}

Coordinates Flock::V_Separation_i(int i) const {
  Coordinates v{0, 0};
  for (int j = 0; j < static_cast<int>(Flock_.size()); j++) {
    if ((Flock_[j].Get_Position() - Flock_[i].Get_Position()).Norm() <= d) {
      v = v - ((Flock_[j].Get_Position() - Flock_[i].Get_Position()) * s);
    }
  }
  return v;
}

Coordinates Flock::V_Allignement_i(int i) const {
  return ((Medium.Get_Velocity() - Flock_[i].Get_Velocity()) * a);
}
Coordinates Flock::V_Cohesion_i(int i) const {
  return ((Medium.Get_Position() - Flock_[i].Get_Position()) * c);
}
Coordinates Flock::Predator_Repulsion(int i) const {
  Coordinates res{0, 0};
  Coordinates Distance = (Predator_.Get_Position() - Flock_[i].Get_Position());
  if (Distance.Norm() < 40) {
    res = Distance * 80 / (-Distance.Norm());
  }
  return res;
}
Coordinates Flock::Obstacles_Repulsion(int i) const {
  Coordinates res{0, 0};
  Coordinates Distance{0, 0};
  for (int j = 0; j < static_cast<int>(Obstacles.size()); j++) {
    Distance = (Obstacles[j] - Flock_[i].Get_Position());
    if (Distance.Norm() < 40) {
      res = res + Distance * 10 / (-Distance.Norm());
    }
  }
  return res;
}
void Flock::Set_Velocity(int i) {
  if (Flock_[i].Get_Velocity().Norm() <= 30) {
    Flock_[i].Set_Velocity(Coordinates(Flock_[i].Get_Velocity() * 1.8));
  }
  if (Flock_[i].Get_Velocity().Norm() >= 70) {
    Flock_[i].Set_Velocity(Flock_[i].Get_Velocity() * 0.8);
  }
}
void Flock::Rules(int i) {
  Coordinates v_i = Flock_[i].Get_Velocity() + V_Allignement_i(i) +
                    V_Cohesion_i(i) + V_Separation_i(i) +
                    Predator_Repulsion(i) + Obstacles_Repulsion(i);
  Flock_[i].Set_Position(Flock_[i].Get_Position() +
                         (Flock_[i].Get_Velocity() / 30));
  Flock_[i].Set_Velocity(v_i);
}

void Flock::Predator_Simulation() {
  Predator_.Predator_Movement();
  if (Predator_.get_Movement_Check() == true) {
    Coordinates v_temp =
        Predator_.Get_Velocity() +
        ((Medium.Get_Position() - Predator_.Get_Position()) * 5 * c);
    if (Predator_.Get_Velocity().Norm() > 35) {
      v_temp = v_temp * 0.8;
    }
    Predator_.Set_Position(Predator_.Get_Position() +
                           Predator_.Get_Velocity() / 30);
    Predator_.Set_Velocity(v_temp);
  }
}
void Flock::Simulation() {
  for (int i = 0; i < static_cast<int>(Flock_.size()); i++) {
    Rules(i);
    Flock_[i].Wall_Hit();
    Set_Velocity(i);
  }
  Predator_Simulation();
  Set_Medium_Boid({Center_Of_Mass(), Medium_Velocity()});
  std::cout << "Medium distance between boids: " << Medium_Distance() << "+/-"
            << Sdv_Center_Of_Mass() << "; "
            << "The Flock moves with medium velocity of: "
            << Medium_Velocity().Norm() << "+/-" << Sdv_Medium_Velocity()
            << '\n';
};
