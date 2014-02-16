#ifndef TILE_H
#define TILE_H

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>


struct Entity;

struct Tile {
  public:
    Tile();
    //Tile(int sprite_x, int sprite_y, int posx, int posy, bool blocks);
    void setSprite(int,int);
    void draw(sf::RenderWindow* window,int,int);
    bool isBlocked();

    bool blocks;
    std::shared_ptr<Entity> hasEntity;

  private:
    int x_;
    int y_;
    sf::Sprite sprite_;
};
#endif
