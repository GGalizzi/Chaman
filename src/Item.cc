#include "Item.h"
#include "Game.h"

Item::Item(TYPE type, std::string name) : type_(type), name_(name), stack_(1) {
  if(name == "Potion") {
    effect_ = &Item::usePotion;
  }
  else {
    effect_ = NULL;
  }
}

Item::~Item() {
}

Item& Item::operator++() {
  ++stack_;
  return *this;
}

Item& Item::operator--() {
  --stack_;
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

bool Item::use(Mob* mob) {
  if (effect_ != NULL) {
    (this->*effect_)(mob);
    return true;
  }
  else {
    Game::log("You can not use that.");
    return false;
  }
}

void Item::usePotion(Mob* mob) {
  Game::log("You drink the potion.");
  mob->heal(25);
}
