#ifndef TILE_H
#define TILE_H

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

struct Tile {
  public:
    Tile();
    //Tile(int sprite_x, int sprite_y, int posx, int posy, bool blocks);
    void setSprite(int,int);
    void draw(sf::RenderWindow* window,int,int);
    bool isBlocked();

    bool blocks;

  private:
    int x_;
    int y_;
    sf::Sprite sprite_;
};
#endif
