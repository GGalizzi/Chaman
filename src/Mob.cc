#include <sstream>
#include "Mob.h"
#include "Game.h"

Mob::Mob() {}

Mob::Mob(FACTION faction, int maxhp, int atk, int def) : 
  maxhp_(maxhp), curhp_(maxhp), atk_(atk), def_(def), faction_(faction) {
}

bool Mob::attack(std::shared_ptr<Mob> defender) {
  defender->curhp_ -= atk_;

  return (defender->curhp_ <= 0) ? true : false;
}

std::string Mob::hpToString() {
  return "HP: "+std::to_string(curhp_) +"/"+std::to_string(maxhp_);
}

void Mob::heal(int ammount) {
  int prevhp = curhp_;
  curhp_ += ammount;
  if (curhp_ > maxhp_) curhp_ = maxhp_;
  std::ostringstream output;
  output << "You heal " << (curhp_ - prevhp) << " HP.";
  Game::log(output.str());
}

bool Mob::sameFactionAs(Mob* m) {
  return faction_ == m->faction_;
}
