#include "Inventory.h"
#include "Game.h"

Inventory::Inventory() {
  invText_.setFont(*Game::fon);
  invText_.setCharacterSize(12);
  background_.setOutlineColor(sf::Color::White);
  background_.setOutlineThickness(Game::SpriteSize/4);
  background_.setFillColor(sf::Color::Black);
}

void Inventory::logContents() {
  std::string logs;

  char letter = 'a';
  for(auto& item : contents_) {
    logs = ") "+item->getName();
    if(item->getStack() > 1)
      logs +=" x"+std::to_string(item->getStack());

    Game::appendStringAfter(invText_, letter+logs+"\n");
    ++letter;
  }

  backgroundRect_ = invText_.getLocalBounds();
  background_.setSize(sf::Vector2f(Game::WindowWidth, Game::WindowHeight));
  background_.setPosition(0,0);
  invText_.setPosition(0,0);

}

Inventory::itemList Inventory::getContents() {
  return contents_;
}

void Inventory::add(Entity* item) {
  Game::log("You picked up "+item->cItem->getName());
  std::shared_ptr<Item> itemPtr;
  itemPtr = item->cItem;
  bool alreadyHave = false;
  for(auto& prevItem : contents_) {
    if(itemPtr->getName() == prevItem->getName()) {
      itemPtr = prevItem;
      alreadyHave = true;
      break;
    }
  }
  if(alreadyHave)
    itemPtr->addStack();
  else
    contents_.push_back(itemPtr);
}

void Inventory::draw(sf::RenderWindow* win) {
  win->draw(background_);
  win->draw(invText_);
}
