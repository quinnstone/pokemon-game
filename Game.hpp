#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

// struct Move
// {
//    std::string name;
//    int damage, amt;
// };

struct Pokemon
{
   Pokemon(std::string _name);
   std::string name, move1Name, move2Name;
   int hp, currentHP, level, move1Damage, move2Damage, move1Amt, move2Amt;
   // bool current
   bool revive;
   // Move *moves[2];

   Pokemon *left;
   Pokemon *right;
};

struct City;

struct Edge
{
    City *c;
    int distance;
};

struct City
{
   std::string cityName, pokemonName;
   bool current;
   std::vector<Edge> Edges; //stores edges to adjacent vertices
};

class Tree
{
   public:
      Tree(){root = NULL;};
      void printTree();
      Pokemon *root;
};

class Game
{
   public:
      Game();
      void intro();
      void chooseStarter();
      void displayMenu();
      void addPokemon(std::string name);
      void addEdge(std::string c1, std::string c2, int distance);
      void addCity(std::string name);
      void setAllCitiesFalse();
      void travelMenu();
      void pokeMart();
      void battle();
      void printPokemon();
      void gameStatus();
      void setCurrentPokemon(std::string name);
      void pokemonCenter();
      bool shayonGym();
      int getNumPokemon(Pokemon* root);
      City* getCurrentCity();
   private:
      std::string playerName;
      std::vector<Pokemon*> pokeList;
      std::vector<City> cities;
      Tree pokeTree;
      int numCoins;
      int numPokeBalls;
      Pokemon* search(std::string title);
};

#endif // GAME_HPP
