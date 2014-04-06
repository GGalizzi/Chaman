#include "Item.h"
#include "Game.h"

Item::Item(TYPE type, std::string name) : type_(type), name_(name), stack_(1) {
  if(name == "Potion") {
    effect_ = &Item::usePotion;
  }
}

Item& Item::operator++() {
  ++stack_;
  return *this;
}

void Item::addStack() {
  ++stack_;
}

std::string Item::getName() {
  return name_;
}

int Item::getStack() {
  return stack_;
}

bool Item::isType(TYPE type) {
  return type_ == type;
}

void Item::use() {
  (this->*effect_)();
}

void Item::usePotion() {
  Game::log("gulp");
}
