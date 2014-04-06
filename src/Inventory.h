#ifndef INVENTORY_H
#define INVENTORY_H

#include <list>
#include <memory>
#include <SFML/Graphics.hpp>

struct Item;
struct Entity;

struct Inventory {
  public:
    typedef std::list<std::shared_ptr<Item>> itemList;

    Inventory();

    itemList getContents();
    std::map< std::string, std::shared_ptr<Item> > getList();
    void logContents();
    void add(Entity*);

    void draw(sf::RenderWindow*);


  private:

    itemList contents_;

    sf::FloatRect backgroundRect_;
    sf::RectangleShape background_;
    sf::Text invText_;


};
#endif
