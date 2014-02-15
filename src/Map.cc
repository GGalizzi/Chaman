#include "Map.h"
#include "Game.h"

Map::Map() {
  width_ = Game::WindowWidth/Game::SpriteSize;
  height_ = Game::WindowHeight/Game::SpriteSize;

  tiles_ = new Tile[width_*height_];

  for (int x = 0; x < width_; x++)
    for (int y = 0; y < height_; y++) {
      if(y == 0 || y == height_-1 || x == 0 || x == width_-1) {
        tiles_[x+y*width_].setSprite(3,2);
        tiles_[x+y*width_].blocks = true;
      }
      else
        tiles_[x+y*width_].blocks = false;
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

bool Map::isBlocked(int x, int y) const {
  const Tile& t = tiles_[x+y*width_];
  return t.blocks;
}

std::shared_ptr<Entity> Map::hasMob(int x, int y) {
  const Tile& t = tiles_[x+y*width_];
  return t.hasMob;
}

void Map::hasMob(int x, int y, std::shared_ptr<Entity> has) {
  tiles_[x+y*width_].hasMob = has;
}
