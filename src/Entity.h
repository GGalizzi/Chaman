#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Map.h"

struct Entity {
  public:
    Entity(int sprite_x, int sprite_y, int posx, int posy, std::shared_ptr<Map> map);
    void move(int,int);


    sf::Sprite getSprite();
  private:
    sf::Sprite sprite_;
    int x_;
    int y_;

    //Map entity is in
    std::shared_ptr<Map> map_;
    
};
#endif
