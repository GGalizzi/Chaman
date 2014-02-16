#ifndef MOB_H
#define MOB_H
#include <memory>
#include <string>

struct Mob {
  public:
    Mob();
    Mob(int maxhp, int atk, int def);
    bool attack(std::shared_ptr<Mob> defender);
    std::string hpToString();
  private:
    int maxhp_;
    int curhp_;
    int atk_;
    int def_;
};
#endif
