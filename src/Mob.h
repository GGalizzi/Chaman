#ifndef MOB_H
#define MOB_H
#include <memory>

struct Mob {
  public:
    Mob();
    Mob(int maxhp, int atk, int def);
    bool attack(std::shared_ptr<Mob> defender);
  private:
    int maxhp_;
    int curhp_;
    int atk_;
    int def_;
};
#endif
