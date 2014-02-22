#include "Game.h"
#include "Tile.h"


Tile::Tile() {
  sprite_.setTexture(*Game::tex);
  sprite_.setTextureRect(sf::IntRect(Game::SpriteSize*14, Game::SpriteSize*3, Game::SpriteSize, Game::SpriteSize));
}

/*
Tile::Tile(int sprite_x, int sprite_y, int posx, int posy, bool blocks) : x_(posx), y_(posy), blocks(blocks) {
  sprite_.setTexture(*Game::tex);
  sprite_.setTextureRect(sf::IntRect(Game::SpriteSize*sprite_x, Game::SpriteSize*sprite_y, Game::SpriteSize, Game::SpriteSize));
  sprite_.setPosition(x_*Game::SpriteSize, y_*Game::SpriteSize);
}*/

void Tile::setSprite(int x, int y) {
  sprite_.setTextureRect(sf::IntRect(Game::SpriteSize*x, Game::SpriteSize*y, Game::SpriteSize, Game::SpriteSize));
}

void Tile::draw(sf::RenderWindow* window, int x, int y) {
  sprite_.setPosition(x*Game::SpriteSize,y*Game::SpriteSize);
  window->draw(sprite_);
}

bool Tile::isBlocked() {
  return blocks;
}
