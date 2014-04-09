#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>
#include <sstream>
#include "Entity.h"
#include "Map.h"


enum class STATE { PLAY, LOOK, INVENTORY, PAUSE, DEAD };

struct Game {
  public:
    typedef std::list<std::shared_ptr<Entity>> entList ;
    static int WindowWidth;
    static int WindowHeight;
    static int GameViewWidth;
    static int GameViewHeight;
    static int StatusViewWidth;
    static int LogViewWidth;
    static int LogViewHeight;
    static int SpriteSize;
    static std::unique_ptr<sf::Texture> tex;
    static std::unique_ptr<sf::Font> fon;
    static STATE state;
    Game();
    ~Game();

    void run();
    bool handleInput(sf::Keyboard::Key key);
    void inventoryInput(char);

    void processAi();
    entList allEnts();

    //Commands
    void look();


    //Text
    static void describe(std::list<std::shared_ptr<Entity>>&);
    static void describe(Entity*);
    static void describe();
    static void appendString(sf::Text&, std::string);
    static void appendStringAfter(sf::Text& text, std::string st);

    static void log(std::string);

    template <class type> static type readStream(std::istringstream& iss);
  private:
    sf::RenderWindow window_;
    sf::View gameView_;
    sf::View statusView_;
    sf::View logView_;

    sf::View menuView_;
    std::shared_ptr<Map> map_;
    std::shared_ptr<Entity> player_;
    std::shared_ptr<Entity> cursor_;
    entList npcs_;
    entList items_;

    bool wait_;
    bool itemInput_;

    sf::Text hpText_;
    static sf::Text logText_;

    static sf::FloatRect backgroundRect_;
    static sf::RectangleShape background_;
    static sf::Text lookText_;


};

template<class type>
type Game::readStream(std::istringstream& iss) {
  type result;

  std::string token;
  std::stringstream resultStream(token);
  std::getline(iss,token);
  resultStream << token;
  resultStream >> result;

  return result;
}

#endif
