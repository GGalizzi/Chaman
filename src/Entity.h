#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include "Mob.h"
#include "Item.h"
#include "Map.h"
#include "Inventory.h"

struct Entity : std::enable_shared_from_this<Entity> {
  public:
    Entity();

    Entity(int sprite_x, int sprite_y, int posx, int posy);
    Entity(int sprite_x, int sprite_y, int posx, int posy, std::string, Mob*);
    Entity(int sprite_x, int sprite_y, int posx, int posy, std::string, Item* item);
    Entity(std::string, int,int);

    void move(int,int, Map* const&, std::list<std::shared_ptr<Entity>>);
    void moveTowards(Entity* const&, Map* const&, std::list<std::shared_ptr<Entity>>);

    bool isMob();


    sf::Sprite getSprite();
    sf::Vector2f posVector();

    sf::Vector2i getPosition();
    void setPosition(sf::Vector2i);
    std::string name;

    //Components
    std::shared_ptr<Mob> cMob;
    std::shared_ptr<Item> cItem;
    Inventory cInventory;

  private:


    void setSprite(int,int);
    sf::Sprite sprite_;
    int x_;
    int y_;


};
#endif
