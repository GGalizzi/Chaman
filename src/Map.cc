#include "Map.h"
#include "Game.h"
#include <fstream>
#include <sstream>
#include <iostream>

Map::Map() {
  width_ = (Game::WindowWidth-200)/Game::SpriteSize;
  height_ = (Game::WindowHeight-100)/Game::SpriteSize;

  tiles_ = new Tile[width_*height_];

  for (int x = 0; x < width_; x++)
    for (int y = 0; y < height_; y++) {
      if(y == 0 || y == height_-1 || x == 0 || x == width_-1 || x == width_/2) {
        placeTile("wall", x,y);
        //tiles_[x+y*width_].setSprite(0,9, sf::Color(232,101,80));
        //tiles_[x+y*width_].blocks = true;
        if(y==height_/2 && x==width_/2){
          tiles_[x+y*width_].setSprite(2,9);
          tiles_[x+y*width_].isDoor = true;
          tiles_[x+y*width_].isLocked = true;
        }
      }
      else {
        tiles_[x+y*width_].blocks = false;
        tiles_[x+y*width_].isDoor = false;
        tiles_[x+y*width_].isLocked = false;
      }
    }
}

Map::~Map() {
  delete[] tiles_;
}

void Map::draw(sf::RenderWindow* window) {
  for (int x = 0; x < width_; x++)
    for (int y = 0; y < height_; y++) {
      tiles_[x+y*width_].draw(window,x,y);
  }
}

void Map::placeTile(std::string name, int x, int y) {
  std::ifstream file("tiles/"+name+".tile");
  int spritex=0;
  int spritey=0;
  bool blocks=false;

  std::string line;

  while( std::getline( file, line ) ) {
    std::istringstream iss(line);

    std::string result;
    if(std::getline(iss,result,':')) {

      if(result == "sprite") {
        std::string token;
        std::stringstream xstream;
        std::getline(iss, token, ',');
        xstream << token;
        xstream >> spritex;

        std::stringstream ystream;
        std::getline(iss,token);
        ystream << token;
        ystream >> spritey;
      }

      else if(result == "blocks") {
        std::string token;
        std::stringstream t(token);
        std::getline(iss,token);
        t << token;
        t >> blocks;
      }
    }
  }

  tiles_[x+y*width_].setSprite(spritex,spritey);
  tiles_[x+y*width_].blocks = blocks;
}

bool Map::isBlocked(int x, int y) const {
  const Tile& t = tiles_[x+y*width_];
  return t.blocks;
}

bool Map::isDoor(int x, int y) const {
  const Tile& t = tiles_[x+y*width_];
  return t.isDoor;
}

bool Map::isLocked(int x,int y, std::list<std::shared_ptr<Item>> inv) const {
  bool isLocked = true;
  const Tile& t = tiles_[x+y*width_];
  if (!t.isLocked) {
    isLocked = false;
  }
  else {
    for (auto& item : inv) {
      if(item->isType(Item::TYPE::KEY)) {
        Game::log("You opened the door with "+item->getName());
        return false;
      }
    }
  }
  return isLocked;
}

void Map::openDoor(int x, int y) {
  tiles_[x+y*width_].isDoor = false;
  tiles_[x+y*width_].blocks = false;

  tiles_[x+y*width_].setSprite(15,2);
}
