#include "Entity.h"
#include "Game.h"

Entity::Entity(int sprite_x, int sprite_y, int posx, int posy, std::shared_ptr<Map> map) : x_(posx), y_(posy), map_(map) {
  sprite_.setTexture(*Game::tex);
  sprite_.setTextureRect(sf::IntRect(Game::SpriteSize*sprite_x, Game::SpriteSize*sprite_y, Game::SpriteSize,Game::SpriteSize));
  sprite_.setPosition(x_*Game::SpriteSize, y_*Game::SpriteSize);
}


//Move receives -1, 0 or 1. Direction where to move.
void Entity::move(int x, int y) {
  if (!map_->isBlocked(x_+x,y_+y)) {
    x_ += x;
    y_ += y;
    sprite_.move(Game::SpriteSize*x, Game::SpriteSize*y);
  }
}

sf::Sprite Entity::getSprite() {
  return sprite_;
}
