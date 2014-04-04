#include <algorithm>
#include <fstream>
#include <sstream>
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
Entity::Entity(int sprite_x, int sprite_y, int posx, int posy, std::string name, Mob* mob) : name(name),cMob(mob),cItem(nullptr), x_(posx), y_(posy) {
  setSprite(sprite_x, sprite_y);
}
//Constructor with ITEM
Entity::Entity(int sprite_x, int sprite_y, int posx, int posy, std::string name, Item* item) : name(name), cMob(nullptr), cItem(item), x_(posx), y_(posy) {
  setSprite(sprite_x, sprite_y);
}

Entity::Entity(std::string name, int posx, int posy) : name(name), x_(posx), y_(posy) {
  // Read corresponding file.
  std::ifstream infile("entities/"+name+".item");

  std::string line;

  //Start reading the lines.
  while(std::getline(infile, line)) {

    //the stream where we'll exctact info from:
    std::istringstream iss(line);

    //Reading between blank spaces.
    do {
      std::string sub; //substring
      iss >> sub;
      if(sub == "sprite") { //sprite coordinates set
        int sprite_x, sprite_y;
        iss >> sprite_x; //move the first coordinate to X
        iss >> sprite_y; //move the second coordinat to Y
        setSprite(sprite_x, sprite_y);
      }

      else if (sub == "type") { // set the appropiate component this Entity should have.
        iss >> sub;

        if (sub == "Item") { // With cItem component.
          std::getline(infile, line); //Next line
          std::istringstream iss(line);
          iss >> sub; // ItemType
          std::string ItemTypeS;
          iss >> ItemTypeS; // = this;
          Item::TYPE ItemType;

          if(ItemTypeS == "KEY") {
            ItemType = Item::TYPE::KEY;
          }
          else {
            ItemType = Item::TYPE::MISC;
          }

          std::getline(infile, line);
          std::string itemName;
          std::getline(infile, itemName); 

          std::shared_ptr<Item> item(new Item(ItemType, itemName));

          cItem = item;
        }
      }
    } while (iss);
  }
}

//Move receives -1, 0 or 1. Direction where to move.
void Entity::move(int x, int y, Map* const& map, std::list<std::shared_ptr<Entity>> ents) {
  int dx = x_+x;
  int dy = y_+y;
  int canMove = false;
  int isMob = false;

  std::shared_ptr<Entity> otherEnt;
  std::list< std::shared_ptr<Entity> > entsInTile;

  canMove = true;
  //Check if there's any entity in the tile we are moving to.
  for (auto& ent : ents) {
    sf::Vector2i pos = ent->getPosition();
    if(pos.x == dx && pos.y == dy) {
      entsInTile.push_back(ent);
      if(ent->isMob()) {
        isMob = true;
        canMove = false;
        otherEnt = ent;
      }
    }

  }
  if ((!map->isBlocked(dx,dy) && canMove && !isMob) || Game::state == STATE::LOOK) {

    x_ += x;
    y_ += y;
    sprite_.move(Game::SpriteSize*x, Game::SpriteSize*y);

    if (Game::state == STATE::LOOK) {
      Game::describe();
      if(!entsInTile.empty()) {
        Game::describe(entsInTile);
      }
    }

  } // if blocked && canMove && !isMob

  else if(map->isDoor(dx,dy)) {
    if(!map->isLocked(dx,dy, cInventory.getContents())) {
      map->openDoor(dx,dy);
    }
    else {
      Game::log("Door is locked.");
    }
  }
  else if(isMob && !cMob->sameFactionAs(otherEnt->cMob.get())) {
    //Attack, and if it dies, remove mob component. Replace sprite graphic with dead corpse.
    if (cMob && cMob->attack(otherEnt->cMob)) {
      //If it dies//

      Game::log(otherEnt->name + " dies.");
      //No longer a mob.
      otherEnt->cMob.reset();

      //Now an item (i.e corpse)
      otherEnt->cItem.reset(new Item(Item::TYPE::CORPSE, "Orc's Corpse"));
      otherEnt->name += "'s Corpse";

      //Set the sprite to dead body
      //otherEnt->sprite_.setTextureRect( sf::IntRect(Game::SpriteSize*5, Game::SpriteSize*2, Game::SpriteSize, Game::SpriteSize) );
      otherEnt->sprite_.setColor(sf::Color::Red);
    }
  }
}

void Entity::moveTowards(Entity* const& target, Map* const& map, std::list<std::shared_ptr<Entity>> ents) {
  int cx = x_ - target->x_;
  int cy = y_ - target->y_;

  int dx,dy;

  if(cx < 0)
    dx = 1;
  else if(cx == 0)
    dx = 0;
  else
    dx = -1;

  if(cy < 0)
    dy = 1;
  else if(cy == 0)
    dy = 0;
  else
    dy = -1;

  move(dx,dy, map, ents);
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

sf::Vector2f Entity::posVector() {
  sf::Vector2f vec(x_*Game::SpriteSize, y_*Game::SpriteSize);
  return vec;
}

sf::Vector2i Entity::getPosition() {
  sf::Vector2i pos(x_,y_);
  return pos;
}

void Entity::setPosition(sf::Vector2i pos) {
  x_ = pos.x;
  y_ = pos.y;
  sprite_.setPosition(x_*Game::SpriteSize, y_*Game::SpriteSize);
}


