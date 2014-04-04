#include "Game.h"


int Game::WindowWidth{1024};
int Game::WindowHeight{720};
int Game::GameViewWidth(WindowWidth*0.75f);
int Game::GameViewHeight(WindowHeight*0.75f);
int Game::StatusViewWidth(WindowWidth*0.25f);
int Game::LogViewWidth(WindowWidth*0.75f);
int Game::LogViewHeight(WindowHeight*0.8f);
int Game::SpriteSize{16};

STATE Game::state = STATE::PLAY;

std::unique_ptr<sf::Texture> Game::tex(new sf::Texture);
std::unique_ptr<sf::Font> Game::fon(new sf::Font);

sf::Text Game::lookText_;
sf::Text Game::logText_;
sf::FloatRect Game::backgroundRect_;
sf::RectangleShape Game::background_;

Game::Game() :
  window_(sf::VideoMode(WindowWidth,WindowHeight), "SFML Rogue"),
  gameView_(),
  statusView_(),
  map_(new Map),
  player_(new Entity(0,0, 1,1, "That's you", new Mob(Mob::FACTION::ALLIES, 520,5,2))),
  cursor_(new Entity(0,0, 1,1)),
  wait_(false)
{
  fon->loadFromFile("Sansation.ttf");
  tex->loadFromFile("ascii.png");
  for(int i = 0; i<8; i++) {
    //std::shared_ptr<Entity> npc(new Entity(0,1, i+5,5, "Orc", new Mob( Mob::FACTION::ORCS, 10, 3, 1)));
    std::shared_ptr<Entity> npc(new Entity("orc", i+5,5));
    npcs_.push_back(npc);


    std::shared_ptr<Entity> item(new Entity("potion", 5,4));
    items_.push_back(item);
  }
  std::shared_ptr<Entity> key(new Entity("key", 10,10));
  items_.push_back(key);

  gameView_.setCenter(player_->posVector());
  gameView_.setSize(GameViewWidth, GameViewHeight);
  gameView_.setViewport(sf::FloatRect(0.f,0.f, 0.75f,0.75f));

  statusView_.setCenter(sf::Vector2f(StatusViewWidth*0.5, WindowHeight/2));
  statusView_.setSize(StatusViewWidth,WindowHeight);
  statusView_.setViewport(sf::FloatRect(0.75f,0.f, 0.25f,1));

  logView_.setCenter(sf::Vector2f(LogViewWidth/2, LogViewHeight/2));
  logView_.setSize(LogViewWidth, LogViewHeight);
  logView_.setViewport(sf::FloatRect(0, 0.8f, 0.75f,0.8f));

  menuView_.setCenter(WindowWidth/2, WindowHeight/2);
  menuView_.setSize(WindowWidth,WindowHeight);
  menuView_.setViewport(sf::FloatRect(0.f,0.f,1,1));

  hpText_.setFont(*fon);
  hpText_.setPosition(0,20);

  logText_.setFont(*fon);
  logText_.setPosition(0,0);
  logText_.setCharacterSize(12);

  lookText_.setFont(*fon);
  lookText_.setCharacterSize(12);

  background_.setOutlineColor(sf::Color::White);
  background_.setOutlineThickness(SpriteSize/4);
  background_.setFillColor(sf::Color::Black);
}

Game::~Game() {
}

void Game::run() {
  while(window_.isOpen() && state != STATE::DEAD) {
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

      if(!player_->cMob) {
        state = STATE::DEAD;
      }

    } //if !wait_


    // Draw stuff
    window_.setView(gameView_);
    window_.clear();
    map_->draw(&window_);

    for(auto& item : items_) {
      window_.draw(item->getSprite());
    }
    for(auto& npc : npcs_) {
      window_.draw(npc->getSprite());
    }

    window_.draw(player_->getSprite());
    if(state == STATE::LOOK) {
      window_.draw(cursor_->getSprite());
      window_.draw(background_);
      window_.draw(lookText_);
    }



    if(state == STATE::PLAY)
      hpText_.setString(player_->cMob->hpToString());
    window_.setView(statusView_);
    window_.draw(hpText_);
    window_.setView(logView_);
    window_.draw(logText_);

    if(state == STATE::INVENTORY) {
      window_.clear();
      window_.setView(menuView_);
      player_->cInventory.draw(&window_);
    }


    window_.display();
  }
}

bool Game::handleInput(sf::Keyboard::Key key) {
  bool wait = true;
  entList entsVec = allEnts();
  std::shared_ptr<Entity> inControl;
  if(state == STATE::PLAY || state == STATE::INVENTORY)
    inControl = player_;
  else if(state == STATE::LOOK)
    inControl = cursor_;
  if (key == sf::Keyboard::Q && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    window_.close();
  if (state == STATE::PLAY || state == STATE::LOOK) {
    if (key == sf::Keyboard::Numpad8) {
      inControl->move(0,-1, map_.get(), entsVec);
      gameView_.setCenter(inControl->posVector());
      wait = false;
    }
    if (key == sf::Keyboard::Numpad2) {
      inControl->move(0,1, map_.get(),  entsVec);
      gameView_.setCenter(inControl->posVector());
      wait = false;
    }
    if (key == sf::Keyboard::Numpad4) {
      inControl->move(-1,0, map_.get(),  entsVec);
      gameView_.setCenter(inControl->posVector());
      wait = false;
    }
    if (key == sf::Keyboard::Numpad6) {
      inControl->move(1,0, map_.get(),  entsVec);
      gameView_.setCenter(inControl->posVector());
      wait = false;
    }
    if (key == sf::Keyboard::Numpad7) {
      inControl->move(-1,-1, map_.get(),  entsVec);
      gameView_.setCenter(inControl->posVector());
      wait = false;
    }
    if (key == sf::Keyboard::Numpad9) {
      inControl->move(1,-1, map_.get(),  entsVec);
      gameView_.setCenter(inControl->posVector());
      wait = false;
    }
    if (key == sf::Keyboard::Numpad3) {
      inControl->move(1,1, map_.get(),  entsVec);
      gameView_.setCenter(inControl->posVector());
      wait = false;
    }
    if (key == sf::Keyboard::Numpad1) {
      inControl->move(-1,1, map_.get(),  entsVec);
      gameView_.setCenter(inControl->posVector());
      wait = false;
    }
    if (key == sf::Keyboard::Numpad5) {
      wait = false;
    }

    if (key == sf::Keyboard::J) {
      wait = true;
      logView_.move(0.f, 12.f);
    }
    if (key == sf::Keyboard::K) {
      wait = true;
      logView_.move(0.f, -12.f);
    }

    if (key == sf::Keyboard::X) {
      describe(player_.get());
      look();
    }

    if (inControl == player_ && key == sf::Keyboard::G) {
      for (auto& item : items_) {
        auto pos = item->getPosition();
        if(pos == player_->getPosition()) {
          player_->cInventory.add(item.get());
          items_.remove(item);
          break;
        }
      }
    }

    if (key == sf::Keyboard::I) {
      Game::state = STATE::INVENTORY;
      player_->cInventory.logContents();
    }

  } // If state == PLAY

  if (key == sf::Keyboard::Escape) {
    state = STATE::PLAY;
  }

  if(state == STATE::LOOK)
    wait = true;
  return wait;
}

void Game::processAi() {
  entList ents = allEnts();
  for(auto& npc : npcs_) {
    if(npc->isMob())
      npc->moveTowards(player_.get(), map_.get(), ents);
  }
}

Game::entList Game::allEnts() {
  entList ents;
  ents.insert(ents.end(), items_.begin(), items_.end());
  ents.insert(ents.end(), npcs_.begin(), npcs_.end());
  ents.push_back(player_);
  return ents;
}

void Game::look() {
  cursor_->setPosition(player_->getPosition());
  state = STATE::LOOK;
}

void Game::describe(entList& ent) {

  lookText_.setPosition(ent.front()->posVector()+sf::Vector2f(SpriteSize,+SpriteSize+SpriteSize/2));
  for(auto it = ent.begin(); it != ent.end(); ++it) {
    appendString(lookText_, (*it)->name);
    if(ent.size() != 0 && it != --(ent.end()))
      appendString(lookText_, "\n");
  }
  backgroundRect_ = lookText_.getLocalBounds();
  background_.setSize(sf::Vector2f(backgroundRect_.width+SpriteSize+SpriteSize/2, backgroundRect_.height+SpriteSize/2));
  background_.setPosition( ent.front()->posVector()+sf::Vector2f(0.f,+SpriteSize+SpriteSize/2) );

}

void Game::describe(Entity* ent) {
  lookText_.setPosition(ent->posVector()+sf::Vector2f(SpriteSize,+SpriteSize+SpriteSize/2));
  lookText_.setString(ent->name);
  backgroundRect_ = lookText_.getLocalBounds();
  background_.setSize(sf::Vector2f(backgroundRect_.width+SpriteSize+SpriteSize/2, backgroundRect_.height+SpriteSize/2));
  background_.setPosition( ent->posVector()+sf::Vector2f(0.f,+SpriteSize+SpriteSize/2) );
}

void Game::describe(/*Nothing*/) {
  lookText_.setString("");
  background_.setSize(sf::Vector2f(0.f,0.f));
}

void Game::appendString(sf::Text& text, std::string st) {
  text.setString(st + text.getString());
}

void Game::appendStringAfter(sf::Text& text, std::string st) {
  text.setString(text.getString() + st);
}

void Game::log(std::string st) {
  appendString(logText_, st+"\n");
}
