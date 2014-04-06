#ifndef ITEM_H 
#define ITEM_H 

#include <string>

struct Item {
  public:
    enum class TYPE { KEY, POTION, CORPSE, MISC };

    Item(TYPE, std::string);

    Item& operator++();
    void addStack();

    int getStack();
    std::string getName();
    bool isType(TYPE);

    void use();

    void usePotion();
  private:
    TYPE type_;
    std::string name_;
    int stack_;

    void (Item::*effect_)();
};
#endif
