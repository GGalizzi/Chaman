#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "Tile.h"
#include "Item.h"

struct Map {
  public:
    Map(unsigned int, std::shared_ptr<Entity>);
    ~Map();
    void setPlayer(std::shared_ptr<Entity>);
    std::shared_ptr<Entity> getPlayer();
    void draw(sf::RenderWindow* window);

    void placeTile(std::string,int,int);

    int getHeight();
    int getWidth();

    //Checks if tile in given coords blocks passage.
    bool isBlocked(int,int) const;
    bool isDoor(int,int) const;
    bool isLocked(int, int, std::list<std::shared_ptr<Item>>) const;
    void openDoor(int,int);

    //Generation
    void genTestRoom();
    void genFromPerlin(const unsigned int& seed);


  private:
    Tile* tiles_;
    int width_;
    int height_;

    std::shared_ptr<Entity> player_;

};

#endif
