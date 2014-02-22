#include "Mob.h"

Mob::Mob() {}

Mob::Mob(FACTION faction, int maxhp, int atk, int def) : 
  maxhp_(maxhp), curhp_(maxhp), atk_(atk), def_(def), faction_(faction) {
}

bool Mob::attack(std::shared_ptr<Mob> defender) {
  defender->curhp_ -= atk_;
  if (defender->curhp_ <= 0) {
    return true;
  }
  return false;
}

std::string Mob::hpToString() {
  return "HP: "+std::to_string(curhp_) +"/"+std::to_string(maxhp_);
}

bool Mob::sameFactionAs(Mob* m) {
  return faction_ == m->faction_;
}
