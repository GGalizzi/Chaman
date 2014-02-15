#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Tile.h"

struct Map {
  public:
    Map();
    ~Map();
    void draw(sf::RenderWindow* window);

    //Checks if tile in given coords blocks passage.
    bool isBlocked(int,int) const;
    //Checks or sets the tile in the given coordinates if it has a mob or not
    std::shared_ptr<Entity> hasMob(int,int);
    void hasMob(int,int,std::shared_ptr<Entity>);

  private:
    Tile* tiles_;
    int width_;
    int height_;

};

#endif
