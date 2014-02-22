#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "Tile.h"
#include "Item.h"

struct Map {
  public:
    Map();
    ~Map();
    void draw(sf::RenderWindow* window);

    //Checks if tile in given coords blocks passage.
    bool isBlocked(int,int) const;
    bool isDoor(int,int) const;
    bool isLocked(int, int, std::list<std::shared_ptr<Item>>) const;
    void openDoor(int,int);


  private:
    Tile* tiles_;
    int width_;
    int height_;

};

#endif
