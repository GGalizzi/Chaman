#include "Entity.h"
#include "Game.h"

//Base Construction function.
void Entity::setSprite(int sprite_x, int sprite_y) {

  sprite_.setTexture(*Game::tex);
  sprite_.setTextureRect(sf::IntRect(Game::SpriteSize*sprite_x, Game::SpriteSize*sprite_y, Game::SpriteSize,Game::SpriteSize));
  sprite_.setPosition(x_*Game::SpriteSize, y_*Game::SpriteSize);

}

//Constructor with no component (i.e cursor_)
Entity::Entity(int sprite_x, int sprite_y, int posx, int posy) : cMob(nullptr), cItem(nullptr), x_(posx), y_(posy) {
  setSprite(sprite_x, sprite_y);
}
//Constructor with MOB
Entity::Entity(int sprite_x, int sprite_y, int posx, int posy, Mob* mob) : cMob(mob),cItem(nullptr), x_(posx), y_(posy) {
  setSprite(sprite_x, sprite_y);
}

//Move receives -1, 0 or 1. Direction where to move.
void Entity::move(int x, int y, Map* const& map) {
  int dx = x_+x;
  int dy = y_+y;
  int canMove = false;
  int isMob = false;
  std::shared_ptr<Entity> hasEntity = map->hasEntity(dx,dy);

  if (!hasEntity || Game::state == STATE::LOOK) {
    canMove = true;
  }
  else {
    if(hasEntity->cMob) {
      canMove = false;
      isMob = true;
    }
    else {
      canMove = true;
    }
  }
  if ((!map->isBlocked(dx,dy) && canMove && !isMob) || Game::state == STATE::LOOK) {

    map->hasEntity(x_,y_,nullptr);
    x_ += x;
    y_ += y;
    map->hasEntity(x_,y_,shared_from_this());

    sprite_.move(Game::SpriteSize*x, Game::SpriteSize*y);
  }

  else if(isMob) {
    //Attack, and if it dies, remove mob component. Replace sprite graphic with dead corpse.
    if (cMob && cMob->attack(hasEntity->cMob)) {
      //If it dies//
      
      hasEntity->cMob.reset();

      hasEntity->cItem.reset(new Item());
      hasEntity->sprite_.setTextureRect( sf::IntRect(Game::SpriteSize*5, Game::SpriteSize*2, Game::SpriteSize, Game::SpriteSize) );
      hasEntity->sprite_.setColor(sf::Color::Red);
    }
  }
}

void Entity::moveTowards(Entity* const& target, Map* const& map) {
  int cx = x_ - target->x_;
  int cy = y_ - target->y_;

  int dx,dy;

  if(cx < 0)
    dx = 1;
  else
    dx = -1;

  if(cy < 0)
    dy = 1;
  else
    dy = -1;

  move(dx,dy, map);
}

bool Entity::isMob() {
  if (cMob)
    return true;
  else
    return false;
}

sf::Sprite Entity::getSprite() {
  return sprite_;
}
