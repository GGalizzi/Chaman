#include "Game.h"

int Game::WindowHeight{480};
int Game::WindowWidth{640};
int Game::SpriteSize{16};

std::unique_ptr<sf::Texture> Game::tex(new sf::Texture);

Game::Game() : 
  window_(sf::VideoMode(WindowWidth,WindowHeight), "SFML Rogue"),
  map_(new Map),
  player_(0,4, 1,1, map_) {
    tex->loadFromFile("ascii.png");
  }

void Game::run() {
  while(window_.isOpen()) {
    sf::Event event;
    while(window_.pollEvent(event)) {
      switch(event.type) {
        case sf::Event::Closed:
          window_.close();
          break;
        case sf::Event::KeyPressed:
          handleInput(event.key.code);
          break;
        default:
          break;
      }
    }
    window_.clear();
    map_->draw(&window_);
    window_.draw(player_.getSprite());
    window_.display();
  }
}

void Game::handleInput(sf::Keyboard::Key key) {
  if (key == sf::Keyboard::Q && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    window_.close();
  if (key == sf::Keyboard::Numpad8)
    player_.move(0,-1);
  if (key == sf::Keyboard::Numpad2)
    player_.move(0,1);
  if (key == sf::Keyboard::Numpad4)
    player_.move(-1,0);
  if (key == sf::Keyboard::Numpad6)
    player_.move(1,0);
  if (key == sf::Keyboard::Numpad7)
    player_.move(-1,-1);
  if (key == sf::Keyboard::Numpad9)
    player_.move(1,-1);
  if (key == sf::Keyboard::Numpad3)
    player_.move(1,1);
  if (key == sf::Keyboard::Numpad1)
    player_.move(-1,1);
}
