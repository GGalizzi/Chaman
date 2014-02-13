#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Tile.h"

struct Map {
  public:
    Map();
    ~Map();
    void draw(sf::RenderWindow* window);
    bool isBlocked(int,int) const;

  private:
    Tile* tiles_;
    int width_;
    int height_;
};

#endif
