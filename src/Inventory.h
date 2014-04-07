#ifndef INVENTORY_H
#define INVENTORY_H

#include <list>
#include <memory>
#include <SFML/Graphics.hpp>

struct Item;
struct Entity;
struct Mob;

struct Inventory {
  public:
    typedef std::list<std::shared_ptr<Item>> itemList;
    typedef std::map< char, std::shared_ptr<Item> > itemMap;

    Inventory();

    itemList getContents();
    itemMap getList();
    void logContents();
    void add(Entity*);
    void destroy(std::shared_ptr<Item>);
    int use(Item*, Mob*);

    void draw(sf::RenderWindow*);


  private:

    itemList contents_;

    sf::FloatRect backgroundRect_;
    sf::RectangleShape background_;
    sf::Text invText_;


};
#endif
