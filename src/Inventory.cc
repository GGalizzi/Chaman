#include "Inventory.h"
#include "Game.h"

void Inventory::logContents() {
  for(auto& item : contents_)
    Game::log(">"+item->getName()+"x"+std::to_string(item->getStack()));
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
