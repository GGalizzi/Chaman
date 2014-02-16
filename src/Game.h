#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Entity.h"
#include "Map.h"


struct Game {
  public:
    static int WindowWidth;
    static int WindowHeight;
    static int SpriteSize;
    static std::unique_ptr<sf::Texture> tex;
    static std::unique_ptr<sf::Font> fon;
    Game();
    ~Game();

    void run();
    bool handleInput(sf::Keyboard::Key key);

    void processAi();
  private:
    sf::RenderWindow window_;
    std::shared_ptr<Map> map_;
    std::shared_ptr<Entity> player_;
    std::vector< std::shared_ptr<Entity> > npcs_;
    std::vector< std::shared_ptr<Entity> > items_;

    bool wait_;

    sf::Text hpText_;


};
#endif
