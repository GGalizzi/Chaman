#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <SFML/Graphics.hpp>
#include "Mob.h"
#include "Item.h"
#include "Map.h"

struct Entity : std::enable_shared_from_this<Entity> {
  public:
    Entity();

    Entity(int sprite_x, int sprite_y, int posx, int posy);
    Entity(int sprite_x, int sprite_y, int posx, int posy, Mob*);
    void move(int,int, Map* const&);
    void moveTowards(Entity* const&, Map* const&);

    bool isMob();


    sf::Sprite getSprite();
    //Components
    std::shared_ptr<Mob> cMob;
    std::shared_ptr<Item> cItem;
  private:


    void setSprite(int,int);
    sf::Sprite sprite_;
    int x_;
    int y_;

};
#endif
