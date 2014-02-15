#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <SFML/Graphics.hpp>
#include "Mob.h"
#include "Map.h"

struct Entity : std::enable_shared_from_this<Entity> {
  public:
    Entity();
    Entity(int sprite_x, int sprite_y, int posx, int posy, Mob*);
    void move(int,int, Map* const&);


    sf::Sprite getSprite();

  private:


    std::shared_ptr<Mob> mob_;
    void setSprite(int,int);
    sf::Sprite sprite_;
    int x_;
    int y_;

};
#endif
