#include "Entity.h"
#include "Game.h"

//Base Construction function.
void Entity::setSprite(int sprite_x, int sprite_y) {

  sprite_.setTexture(*Game::tex);
  sprite_.setTextureRect(sf::IntRect(Game::SpriteSize*sprite_x, Game::SpriteSize*sprite_y, Game::SpriteSize,Game::SpriteSize));
  sprite_.setPosition(x_*Game::SpriteSize, y_*Game::SpriteSize);

}

//Constructor with MOB
Entity::Entity(int sprite_x, int sprite_y, int posx, int posy, Mob* mob) : mob_(mob), x_(posx), y_(posy) {
  setSprite(sprite_x, sprite_y);
}

//Move receives -1, 0 or 1. Direction where to move.
void Entity::move(int x, int y, Map* const& map) {
  int dx = x_+x;
  int dy = y_+y;
  std::shared_ptr<Entity> mobToAttack = map->hasMob(dx,dy);
  if (!map->isBlocked(dx,dy) && mobToAttack == nullptr) {
    x_ += x;
    y_ += y;

    map->hasMob(x_-x,y_-y,nullptr);
    map->hasMob(x_,y_,mobToAttack);
    sprite_.move(Game::SpriteSize*x, Game::SpriteSize*y);
  }

  else if(mobToAttack) {
    //Attack, and if it dies, remove mob component. Replace sprite graphic with dead corpse.
    if (mob_->attack(mobToAttack->mob_)) {
      mobToAttack->sprite_.setTextureRect( sf::IntRect(Game::SpriteSize*5, Game::SpriteSize*2, Game::SpriteSize, Game::SpriteSize) );
      mobToAttack->sprite_.setColor(sf::Color::Red);

    }
  }
}

sf::Sprite Entity::getSprite() {
  return sprite_;
}
