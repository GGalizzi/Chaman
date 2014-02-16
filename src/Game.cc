#include "Game.h"


int Game::WindowHeight{720};
int Game::WindowWidth{1024};
int Game::SpriteSize{11};

STATE Game::state = STATE::PLAY;

std::unique_ptr<sf::Texture> Game::tex(new sf::Texture);
std::unique_ptr<sf::Font> Game::fon(new sf::Font);

Game::Game() :
  window_(sf::VideoMode(WindowWidth,WindowHeight), "SFML Rogue"),
  map_(new Map),
  player_(new Entity(0,4, 1,1, new Mob(120,5,2))),
  cursor_(new Entity(9,0, 1,1)),
  wait_(false)
  {
    fon->loadFromFile("Sansation.ttf");
    tex->loadFromFile("ascii.png");
    map_->hasEntity(1,1, player_);
    for(int i = 0; i<4; i++) {
      std::shared_ptr<Entity> npc(new Entity(15,4, i+5,5, new Mob(10, 3, 1)));
      npcs_.push_back(npc);
      map_->hasEntity(i+5,5, npc);
    }

    hpText_.setFont(*fon);
    hpText_.setPosition(WindowWidth-190,20);

  }

Game::~Game() {
}

void Game::run() {
  while(window_.isOpen()) {
    sf::Event event;

    wait_ = true;
    while(window_.pollEvent(event)) {
      switch(event.type) {
        case sf::Event::Closed:
          window_.close();
          break;
        case sf::Event::KeyPressed:
          wait_ = handleInput(event.key.code);
          break;
        default:
          break;
      }
    }

    if(!wait_) {
      processAi();

      //Check deaths.
      auto it = npcs_.begin();

      for (/*it*/; it !=npcs_.end();) {
        if (!(*it)->cMob) {
          items_.push_back(*it);
          it = npcs_.erase(it);
        }
        else {
          ++it;
        }
      }
    }


    // Draw stuff
    window_.clear();
    map_->draw(&window_);

    for(auto& item : items_) {
      window_.draw(item->getSprite());
    }
    for(auto& npc : npcs_) {
      window_.draw(npc->getSprite());
    }

    window_.draw(player_->getSprite());
    if(state == STATE::LOOK)
      window_.draw(cursor_->getSprite());
    hpText_.setString(player_->cMob->hpToString());
    window_.draw(hpText_);
    window_.display();
  }
}

bool Game::handleInput(sf::Keyboard::Key key) {
  bool wait = true;
  std::shared_ptr<Entity> inControl;
  if(state == STATE::PLAY)
    inControl = player_;
  else if(state == STATE::LOOK)
    inControl = cursor_;
  if (key == sf::Keyboard::Q && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    window_.close();
  if (key == sf::Keyboard::Numpad8) {
    inControl->move(0,-1, map_.get());
    wait = false;
  }
  if (key == sf::Keyboard::Numpad2) {
    inControl->move(0,1, map_.get());
    wait = false;
  }
  if (key == sf::Keyboard::Numpad4) {
    inControl->move(-1,0, map_.get());
    wait = false;
  }
  if (key == sf::Keyboard::Numpad6) {
    inControl->move(1,0, map_.get());
    wait = false;
  }
  if (key == sf::Keyboard::Numpad7) {
    inControl->move(-1,-1, map_.get());
    wait = false;
  }
  if (key == sf::Keyboard::Numpad9) {
    inControl->move(1,-1, map_.get());
    wait = false;
  }
  if (key == sf::Keyboard::Numpad3) {
    inControl->move(1,1, map_.get());
    wait = false;
  }
  if (key == sf::Keyboard::Numpad1) {
    inControl->move(-1,1, map_.get());
    wait = false;
  }
  if (key == sf::Keyboard::L) {
    look();
  }

  if (key == sf::Keyboard::Escape) {
    state = STATE::PLAY;
  }

  if(state == STATE::LOOK)
    wait = true;
  return wait;
}

void Game::processAi() {
  for(auto& npc : npcs_) {
    if(npc->isMob())
      npc->moveTowards(player_.get(), map_.get());
  }
}

void Game::look() {
  state = STATE::LOOK;
}
