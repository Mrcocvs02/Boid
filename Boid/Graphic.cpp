#include "Graphic.hpp"
Game::Game(float d, float s, float a, float c, int n)
    : Flock_{d, s, a, c, n},
      Display_Height{650},
      Display_Width{1200},
      Boid_i{2.f, 3},
      Predator_Shape{4.f},
      Flock_Center{2.0f},
      Obstacle_i{4.0f},
      Data{sf::Vector2f((Display_Width / 5 + 15), (Display_Height / 5))},
      Sdv_Flock_Velocity{sf::Vector2f(10.f, 2.f)},
      FPS{30},
      Play_Button{true},
      Data_Height{(static_cast<float>(Display_Width) / 5)},
      Data_Width{(static_cast<float>(Display_Width) / 5) + 15}{}


void Game::Set_Immages() {
  Boid_i.setOutlineThickness(1.f);
  Boid_i.setFillColor(sf::Color(28, 229, 198));

  Predator_Shape.setOutlineThickness(1.f);
  Predator_Shape.setFillColor(sf::Color::Red);

  Flock_Center.setOutlineThickness(1.f);
  Flock_Center.setFillColor(sf::Color::Red);

  Data.setFillColor(sf::Color::Transparent);
  Data.setOutlineThickness(2.f);
  Data.setPosition(2., (Display_Height - Data_Height - 2));

  Obstacle_i.setOutlineThickness(1.f);
  Obstacle_i.setFillColor(sf::Color(108, 25, 44));

  Sdv_Flock_Velocity.setFillColor(sf::Color::Blue);
}

float Game::Angle(Coordinates const& v) {
  float angle = (float)(atan2(v.Get_x(), -v.Get_y()) * 180 / M_PI);
  return angle;
}

void Game::Close_Window(sf::RenderWindow* window) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    window->close();
    std::cout << "program terminated" << '\n';
    exit(0);
  };
}

void Game::Play_button() {
  if (Play_Button == true) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
      Play_Button = false;
    };
  } else {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      Play_Button = true;
    }

    for (unsigned long int i = 0; i < Flock_.get_flock().size(); i++) {
      Flock_.get_flock()[i].Set_Velocity(Flock_.Predator_Repulsion(i));
      Flock_.get_flock()[i].Wall_Hit();
      Flock_.get_flock()[i].Set_Position(
          Flock_.get_flock()[i].Get_Position() +
          (Flock_.get_flock()[i].Get_Velocity() / FPS));
    }
  }
}

void Game::Draw(sf::RenderWindow* window) {
  for (int i = 0; i < static_cast<int>(Flock_.get_flock().size()); i++) {
    Boid_i.setPosition(Flock_.get_flock()[i].Get_Position().Get_x(),
                       Flock_.get_flock()[i].Get_Position().Get_y());
    float theta = Angle(Flock_.get_flock()[i].Get_Velocity());
    Boid_i.setRotation(theta);
    window->draw(Boid_i);
  }

  for (int i = 0; i < static_cast<int>(Flock_.Get_Obstacles().size()); i++) {
    Obstacle_i.setPosition(Flock_.Get_Obstacles()[i].Get_x(),
                           Flock_.Get_Obstacles()[i].Get_y());
    window->draw(Obstacle_i);
  }

  Predator_Shape.setPosition(Flock_.Get_Predator().Get_Position().Get_x(),
                             Flock_.Get_Predator().Get_Position().Get_y());
  window->draw(Predator_Shape);

  float graph_height =
      Display_Height -
      (Data_Height * (Flock_.Get_Medium_Boid().Get_Velocity().Norm() / 75));
  sf::RectangleShape Graph(sf::Vector2f(10, graph_height));
  Graph.setFillColor(sf::Color::Red);
  Graph.setOutlineThickness(1.f);
  if (graph_height < Display_Height - Data_Height)
    graph_height = Display_Height - Data_Height;

  Graph.setPosition(10, graph_height);

  Flock_Center.setFillColor(sf::Color::Green);
  Flock_Center.setPosition(
      (Flock_.Get_Medium_Boid().Get_Position().Get_x() / 5) - 3,
      (Flock_.Get_Medium_Boid().Get_Position().Get_y() / 5) + Display_Height -
          Data_Height - 3);

  float sdv_CM = Flock_.Sdv_Center_Of_Mass();
  sf::CircleShape Sdv_Flock_Center;
  Sdv_Flock_Center.setRadius(sdv_CM / 5);
  Sdv_Flock_Center.setOutlineThickness(1.f);
  Sdv_Flock_Center.setFillColor(sf::Color::Transparent);
  Sdv_Flock_Center.setPosition(Flock_Center.getPosition() -
                               sf::Vector2f(sdv_CM / 5 - 2, sdv_CM / 5 - 2));

  float sdv_MV = Flock_.Sdv_Medium_Velocity();
  Sdv_Flock_Velocity.setPosition(10., (graph_height - sdv_MV));
  window->draw(Sdv_Flock_Velocity);

  Sdv_Flock_Velocity.setPosition(10., (graph_height + sdv_MV));

  window->draw(Flock_Center);
  window->draw(Sdv_Flock_Center);
  window->draw(Graph);
  window->draw(Sdv_Flock_Velocity);
  window->draw(Data);
}

void Game::Run(sf::RenderWindow* window) {
  window->setFramerateLimit(FPS);
  int Current_Frame = 0;
  Set_Immages();
  while (window->isOpen()) {
    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) window->close();
    }
    while (Current_Frame / 30 < 600) {
      Close_Window(window);
      window->clear(sf::Color(22, 28, 72));
      Play_button();
      if (Play_Button == true) {
        Flock_.Simulation();
      }
      Draw(window);
      window->display();
      Current_Frame++;
    }
  }
}