#include "Map.h"
#include "Game.h"
#include "PerlinNoise.h"
#include <fstream>
#include <sstream>
#include <iostream>

Map::Map() {
  width_ = (Game::WindowWidth-200)/Game::SpriteSize;
  height_ = (Game::WindowHeight-100)/Game::SpriteSize;

  tiles_ = new Tile[width_*height_];

  genFromPerlin(123229249u);
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

  std::string line;

  while( std::getline( file, line ) ) {
    std::istringstream iss(line);

    std::string result;
    if(std::getline(iss,result,':')) {

      if(result == "sprite") {
        int spritex;
        int spritey;

        std::string token;
        std::stringstream xstream;
        std::getline(iss, token, ',');
        xstream << token;
        xstream >> spritex;

        std::stringstream ystream;
        std::getline(iss,token);
        ystream << token;
        ystream >> spritey;

        tiles_[x+y*width_].setSprite(spritex,spritey);
      }

      else if(result == "blocks") {
        tiles_[x+y*width_].blocks = Game::readStream<bool>(iss);
      }

      else if(result == "isDoor") {
        tiles_[x+y*width_].isDoor = Game::readStream<bool>(iss);
      }
      else if(result == "isLocked") {
        tiles_[x+y*width_].isLocked = Game::readStream<bool>(iss);
      }
    }
  }
}

int Map::getHeight() {
  return height_;
}

int Map::getWidth() {
  return width_;
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

void Map::genTestRoom() {
  for (int x = 0; x < width_; x++)
    for (int y = 0; y < height_; y++) {
      if(y == 0 || y == height_-1 || x == 0 || x == width_-1 || x == width_/2) {
        placeTile("wall", x,y);
        if(y==height_/2 && x==width_/2){
          placeTile("locked_door",x,y);
        }
      }
      else {
        tiles_[x+y*width_].blocks = false;
        tiles_[x+y*width_].isDoor = false;
        tiles_[x+y*width_].isLocked = false;
      }
    }
}

void Map::genFromPerlin(const unsigned int& seed) {
  PerlinNoise pn(seed);

  for(int Y=0; Y < height_; ++Y) {
    for(int X=0; X < width_; ++X) {
      double x = (double)X/((double) width_);
      double y = (double)Y/((double) height_);

      double n = pn.noise(10 * x, 10 * y, 0.8);

      if(n < 0.35) {
        placeTile("wall", X,Y);
      }
    }
  }
}
