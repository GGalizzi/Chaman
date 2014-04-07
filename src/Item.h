#ifndef ITEM_H 
#define ITEM_H 

#include <string>

struct Mob;

struct Item {
  public:
    enum class TYPE { KEY, POTION, CORPSE, MISC };

    Item(TYPE, std::string, int potency=1);
    ~Item();

    Item& operator++();
    Item& operator--();
    void addStack();

    int getStack();
    std::string getName();
    bool isType(TYPE);

    bool use(Mob*);

    void usePotion(Mob*);
  private:
    TYPE type_;
    std::string name_;
    int potency_;
    int stack_;

    void (Item::*effect_)(Mob*);
};
#endif
