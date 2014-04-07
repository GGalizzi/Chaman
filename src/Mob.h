#ifndef MOB_H
#define MOB_H
#include <memory>
#include <string>

struct Mob {
  public:
    enum class FACTION { ALLIES, ORCS, NEUTRAL };

    Mob();
    Mob(FACTION, int maxhp, int atk, int def);
    bool attack(std::shared_ptr<Mob> defender);
    std::string hpToString();

    void heal(int);

    bool sameFactionAs(Mob*);
  private:

    int maxhp_;
    int curhp_;
    int atk_;
    int def_;

    FACTION faction_;
};
#endif
