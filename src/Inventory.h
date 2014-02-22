#ifndef INVENTORY_H
#define INVENTORY_H

#include <list>
#include <memory>

struct Item;
struct Entity;

struct Inventory {
  public:
    typedef std::list<std::shared_ptr<Item>> itemList;

    itemList getContents();
    void logContents();
    void add(Entity*);


  private:

    itemList contents_;

};
#endif
