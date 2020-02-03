#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include "Game.hpp"
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

Game::Game()
{
   numCoins = 100;
   numPokeBalls = 3;
}

Pokemon::Pokemon(string _name)
{
   name = _name;
   hp = 25;
   currentHP = 25;
   level = 1;
   left = right = NULL;
   // current = false;
   move1Amt = 5;
   move2Amt = 3;
   move1Damage = 8;
   move2Damage = 12;
   if (name == "Charmander")
   {
      move1Name = "Scratch";
      move2Name = "Ember";
   }
   else if (name == "Squirtle")
   {
      move1Name = "Water Gun";
      move2Name = "Bubble";
   }
   else if (name == "Bulbosaur")
   {
      move1Name = "Vine Whip";
      move2Name = "Take Down";
   }
   else if (name == "Geodude")
   {
      move1Name = "Tackle";
      move2Name = "Rollout";
   }
   else if (name == "Staryu")
   {
      move1Name = "Water Gun";
      move2Name = "Rapid Spin";
   }
   else if (name == "Pikachu")
   {
      move1Name = "Thunder Shock";
      move2Name = "Quick Attack";
   }
   else if (name == "Tangela")
   {
      move1Name = "Constrict";
      move2Name = "Absorb";
   }
   else if (name == "Kadabra")
   {
      move1Name = "Confusion";
      move2Name = "Psybeam";
   }
   else if (name == "Koffing")
   {
      move1Name = "Smog";
      move2Name = "Assurance";
   }
   else if (name == "Lapras")
   {
      move1Name = "Ice Shard";
      move2Name = "Water Pulse";
   }
   else if (name == "Dugtrio")
   {
      move1Name = "Night Slash";
      move2Name = "Sand Tomb";
   }
   else if (name == "Ponyta")
   {
      move1Name = "Flame Wheel";
      move2Name = "Stomp";
   }
}

void Game::intro()
{
   cout << "Hello, what is your name?" << endl;
   getline(cin, this->playerName);
   cout << endl << "Welcome, " << playerName << ". Here are a few things to know as you play the game:" << endl
   << "1. There are 12 different Pokémon you can catch." << endl
   << "   Visit all of the cities to catch 'em all!" << endl
   << "2. You start with 100 coins and 3 PokéBalls." << endl
   << "3. When you win a battle, you will win coins and level up your Pokémon." << endl
   << "4. Beat the final gym leader, Shayon Gupta, to win the game!" << endl << endl
   << "Please choose a starting Pokémon." << endl;
}

void Game::chooseStarter()
{
   int starterNum;
   string startNum, starterName = "";
   cout << "Enter a Pokémon's corresponding number to choose it:" << endl;
   cout << "(1) Charmander, (2) Squirtle, (3) Bulbosaur" << endl;
   getline(cin, startNum);
   starterNum = stoi(startNum);
   while (starterName == "")
   {
      if (starterNum >= 1 && starterNum <= 3)
      {
         if (starterNum == 1)
            starterName = "Charmander";
         else if (starterNum == 2)
            starterName = "Squirtle";
         else
            starterName = "Bulbosaur";
      }
      else
         cout << "Please choose a valid number." << endl;
   }
   addPokemon(starterName);
   cout << endl << "Congratulations, " << playerName << "! You have chosen " << starterName << " as your starting Pokémon!"
   << endl << "Good luck!" << endl;
   gameStatus();
}

void Game::addEdge(string c1, string c2, int distance)
{
   for (int i = 0; i < cities.size(); i++)
   {
      if (cities[i].cityName == c1)
      {
         for (int j = 0; j < cities.size(); j++)
         {
            if (cities[j].cityName == c2)
            {
               Edge newEdge;
               newEdge.c = &cities[j];
               newEdge.distance = distance;
               cities[i].Edges.push_back(newEdge);
            }
         }
      }
   }
}

void Game::addCity(std::string name)
{
   City newCity;
   newCity.cityName = name;
   if (name == "Pewter City")
   {
      newCity.pokemonName = "Geodude";
      newCity.current = true;
   }
   else
   {
      if (name == "Cerulean City")
         newCity.pokemonName = "Staryu";
      else if (name == "Vermilion City")
         newCity.pokemonName = "Pikachu";
      else if (name == "Celadon City")
         newCity.pokemonName = "Tangela";
      else if (name == "Saffron City")
         newCity.pokemonName = "Kadabra";
      else if (name == "Fuchsia City")
         newCity.pokemonName = "Koffing";
      else if (name == "Lavender City")
         newCity.pokemonName = "Lapras";
      else if (name == "Viridian City")
         newCity.pokemonName = "Dugtrio";
      else if (name == "Shayon City")
         newCity.pokemonName = "Ponyta";
      newCity.current = false;
   }
   cities.push_back(newCity);
}

void Game::setAllCitiesFalse()
{
   for (int i = 0; i < cities.size(); i++)
      cities[i].current = false;
}

City* Game::getCurrentCity()
{
   for (int i = 0; i < cities.size(); i++)
   {
      if (cities[i].current)
      {
         return &cities[i];
      }
   }
   return NULL;
}

void Game::addPokemon(string name)
{
   Pokemon *newPokemon = new Pokemon(name);
   if (pokeTree.root == NULL)
   {
    pokeTree.root = newPokemon;
    pokeList.push_back(newPokemon);
    return;
   }
   Pokemon *temp = pokeTree.root;
   while (temp != NULL)
   {
      if (name < temp->name)
      {
         if (temp->left == NULL)
         {
            temp->left = newPokemon;
            break;
         }
         else
           temp = temp->left;
      }
      else
      {
         if (temp->right == NULL)
         {
           temp->right = newPokemon;
           break;
        }
         else
           temp = temp->right;
      }
   }
   pokeList.push_back(newPokemon);
}

void printPokemonHelper(Pokemon* p)
{
   if (p == NULL)
      return;
   printPokemonHelper(p->left);
   cout << p->name << " (Level " << p->level << ") " << p->currentHP << "/" << p->hp << " HP" << endl;
   printPokemonHelper(p->right);
}


void Game::printPokemon()
{
   Pokemon *p = pokeTree.root;
   cout << endl;
   cout << "+++++++++++++++++++++++++++++" << endl;
   printPokemonHelper(p);
   cout << "+++++++++++++++++++++++++++++" << endl;
}

void Game::travelMenu()
{
   string strInput;
   int input;
   City *currentCity = getCurrentCity();
   cout << endl << "You are currently in " << currentCity->cityName << ". Where would you like to travel to?" << endl << endl;
   for (int i = 0; i < currentCity->Edges.size(); i++)
      cout << i + 1 << ". " << currentCity->Edges[i].c->cityName << endl;
   getline(cin, strInput);
   input = stoi(strInput);
   while (input < 0 || input > currentCity->Edges.size())
   {
      cout << endl << "Enter a valid number." << endl;
      getline(cin, strInput);
      input = stoi(strInput);
   }
   setAllCitiesFalse();
   currentCity->Edges[input - 1].c->current = true;
   cout << endl << "Welcome to " << currentCity->Edges[input - 1].c->cityName << "!" << endl;
   gameStatus();
}

void Game::pokeMart()
{
   string strInput;
   int input;
   bool quit = false;
   cout << endl << "Welcome to the PokeMart! What would you like to buy?" << endl;
   while (!quit)
   {
      cout << endl << "======Shop Menu======" << endl
           << "1. PokéBall - 10 coins" << endl
           << "2. Quit" << endl;
      getline(cin, strInput);
      input = stoi(strInput);
      while (input != 1 && input != 2)
      {
         cout << endl << "Enter a valid number." << endl;
         getline(cin, strInput);
         input = stoi(strInput);
      }
      if (input == 1)
      {
         cout << endl << "How many PokéBalls would you like to buy?" << endl;
         getline(cin, strInput);
         input = stoi(strInput);
         while (input * 10 > numCoins)
         {
            cout << endl << "You do not have enough coins to purchase this many PokéBalls. "
                 << endl << "Enter a valid number." << endl;
            getline(cin, strInput);
            input = stoi(strInput);
         }
         cout << endl << "You have purchased " << input << " PokéBalls." << endl;
         for (int i = 0; i < input; i++)
         {
            numPokeBalls++;
            numCoins -= 10;
         }
         gameStatus();

         cout << endl << "Would you like to buy anything else? (1) Yes, (2) No" << endl;
         getline(cin, strInput);
         input = stoi(strInput);
         while (input != 1 && input != 2)
         {
            cout << endl << "Enter a valid number." << endl;
            getline(cin, strInput);
            input = stoi(strInput);
         }
         if (input == 2)
         {
            cout << endl << "Thank you for shopping at the PokeMart! Have a nice day!" << endl;
            quit = true;
         }
      }
      else
         quit = true;
   }
}

// void Game::setCurrentPokemon(string name)
// {
//    Pokemon *setCurrent = search(name);
//    setCurrent->current = true;
// }

Pokemon* Game::search(string name)
{
   Pokemon *temp = pokeTree.root;
   while (temp != NULL)
   {
     if (name == temp->name)
      return temp;
     else if (name < temp->name)
      temp = temp->left;
     else
      temp = temp->right;
   }
   return NULL;
}

void Game::battle()
{
   City *currentCity = getCurrentCity();
   cout << endl << "You have encountered a wild " << currentCity->pokemonName << "!" << endl
        << "Do you want to (1) Battle, (2) Throw a PokéBall, (3) Run" << endl;
   string strInput, moveStrInput;
   int input, moveInput;
   getline (cin, strInput);
   input = stoi(strInput);
   while (input < 1 || input > 3)
   {
      cout << "Enter a valid number." << endl;
      getline (cin, strInput);
      input = stoi(strInput);
   }
   if (input == 1)
   {
      int enemyHP = 25;
      bool myTurn = true, over = false;
      int numPokemon = getNumPokemon(pokeTree.root);
      Pokemon *currentPokemon = pokeList[0];
      if (numPokemon > 1)
      {
         cout << endl << "Which Pokemon would you like to use to start the battle?" << endl;
         for (int i = 0; i < pokeList.size(); i++)
         {
            cout << i + 1 << ". " << pokeList[i]->name << endl;
         }
         getline(cin, strInput);
         input = stoi(strInput);
         while (input < 1 || input > pokeList.size())
         {
            cout << endl << "Please enter a valid Pokémon." << endl;
            getline(cin, strInput);
            input = stoi(strInput);
         }
         currentPokemon = search(pokeList[input - 1]->name);
      }
      while (!over)
      {
         if (myTurn)
         {
            cout << endl << "Which move would you like to use? " << endl
                 << "(1) " << pokeList[input - 1]->move1Name << " (2) " << pokeList[input - 1]->move2Name << endl;
            getline(cin, moveStrInput);
            moveInput = stoi(moveStrInput);
            while (moveInput != 1 && moveInput != 2)
            {
               cout << "Enter a valid number." << endl;
               getline(cin, moveStrInput);
               moveInput = stoi(moveStrInput);
            }
            if (moveInput == 1)
            {
               enemyHP -= currentPokemon->move1Damage;
               if (enemyHP <= 0)
               {
                  enemyHP = 0;
                  over = true;
               }
               cout << endl << currentPokemon->name << ": " << currentPokemon->currentHP << "/" << currentPokemon->hp << " HP" << endl;
               cout << currentCity->pokemonName << ": " << enemyHP << "/25 HP" << endl;
               cout << "================================" << endl;
            }
            else
            {
               enemyHP -= currentPokemon->move2Damage;
               if (enemyHP <= 0)
               {
                  enemyHP = 0;
                  over = true;
               }
               cout << endl << currentPokemon->name << ": " << currentPokemon->currentHP << "/" << currentPokemon->hp << " HP" << endl;
               cout << currentCity->pokemonName << ": " << enemyHP << "/25 HP" << endl;
               cout << "================================" << endl;
            }
         }
         else
         {
            sleep_until(system_clock::now() + seconds(2));
            cout << endl << currentCity->pokemonName << " used Scratch." << endl;
            currentPokemon->currentHP -= 5;
            if (currentPokemon->currentHP <= 0)
            {
               currentPokemon->currentHP = 0;
               over = true;
            }
            cout << endl << currentPokemon->name << ": " << currentPokemon->currentHP << "/" << currentPokemon->hp << " HP" << endl;
            cout << currentCity->pokemonName << ": " << enemyHP << "/25 HP" << endl;
            cout << "================================" << endl;
         }
         myTurn = !myTurn;
      }
      if (!myTurn)
      {
         currentPokemon->level++;
         numCoins += 15;
         currentPokemon->hp += 5;
         currentPokemon->move1Damage++;
         currentPokemon->move2Damage++;
         cout << endl << "You have defeated the wild " << currentCity->pokemonName << "!" << endl;
         cout << currentPokemon->name << " has leveled up to level " << currentPokemon->level << "." << endl;;
      }
      else
      {
         cout << endl << "The wild " << currentCity->pokemonName << " defeated you." << endl;
         cout << "You have been transported to the local Pokémon Center." << endl;
         pokemonCenter();
      }
   }
   else if (input == 2)
   {
      if (numPokeBalls > 0)
      {
         numPokeBalls--;
         int randNum = rand() % 10 + 1;
         // cout << "randNum = " << randNum << endl;
         if (randNum >= 1 && randNum <= 6)
         {
            cout << endl << "You have caught the wild " << currentCity->pokemonName << "!" << endl;
            addPokemon(currentCity->pokemonName);
         }
         else
            cout << endl << "Oh no! The wild " << currentCity->pokemonName << " escaped!" << endl;
      }
      else
         cout << "You do not have any PokéBalls. Visit the PokéMart to buy some more!" << endl;
   }
   else
      cout << endl << "You escaped safely!" << endl;
   gameStatus();
   printPokemon();
}

bool Game::shayonGym()
{
   string strInput, moveStrInput, shayonPokemonName = "Shayon Jr.";
   int input, moveInput, enemyHP = 60;
   bool myTurn = true, over = false;
   int numPokemon = getNumPokemon(pokeTree.root);
   Pokemon *currentPokemon = pokeList[0];
   cout << endl << "You are about to fight the final gym leader, Shayon Gupta," << endl
        << "King of the Data Structure Pokémon..." << endl;
   if (numPokemon > 1)
   {
      cout << endl << "Which Pokemon would you like to use to start the battle?" << endl;
      for (int i = 0; i < pokeList.size(); i++)
      {
         cout << i + 1 << ". " << pokeList[i]->name << endl;
      }
      getline(cin, strInput);
      input = stoi(strInput);
      while (input < 1 || input > pokeList.size())
      {
         cout << endl << "Please enter a valid Pokémon." << endl;
         getline(cin, strInput);
         input = stoi(strInput);
      }
      currentPokemon = search(pokeList[input - 1]->name);
   }
   while (!over)
   {
      if (myTurn)
      {
         cout << endl << "Which move would you like to use? " << endl
              << "(1) " << currentPokemon->move1Name << " (2) " << currentPokemon->move2Name << endl;
         getline(cin, moveStrInput);
         moveInput = stoi(moveStrInput);
         while (moveInput != 1 && moveInput != 2)
         {
            cout << "Enter a valid number." << endl;
            getline(cin, moveStrInput);
            moveInput = stoi(moveStrInput);
         }
         if (moveInput == 1)
         {
            enemyHP -= currentPokemon->move1Damage;
            if (enemyHP <= 0)
            {
               enemyHP = 0;
               over = true;
            }
            cout << endl << currentPokemon->name << ": " << currentPokemon->currentHP << "/" << currentPokemon->hp << " HP" << endl;
            cout << shayonPokemonName << ": " << enemyHP << "/60 HP" << endl;
            cout << "================================" << endl;
         }
         else
         {
            enemyHP -= currentPokemon->move2Damage;
            if (enemyHP <= 0)
            {
               enemyHP = 0;
               over = true;
            }
            cout << endl << currentPokemon->name << ": " << currentPokemon->currentHP << "/" << currentPokemon->hp << " HP" << endl;
            cout << shayonPokemonName << ": " << enemyHP << "/60 HP" << endl;
            cout << "================================" << endl;
         }
      }
      else
      {
         sleep_until(system_clock::now() + seconds(2));
         cout << endl << shayonPokemonName << " used nullPtr!" << endl;
         currentPokemon->currentHP -= 10;
         if (currentPokemon->currentHP <= 0)
         {
            currentPokemon->currentHP = 0;
            over = true;
         }
         cout << endl << currentPokemon->name << ": " << currentPokemon->currentHP << "/" << currentPokemon->hp << " HP" << endl;
         cout << shayonPokemonName << ": " << enemyHP << "/60 HP" << endl;
         cout << "================================" << endl;
      }
      myTurn = !myTurn;
   }
   if (!myTurn)
   {
      currentPokemon->level++;
      numCoins += 15;
      currentPokemon->hp += 5;
      currentPokemon->move1Damage++;
      currentPokemon->move2Damage++;
      cout << endl << "You have defeated Shayon Gupta and his prized Pokémon, " << shayonPokemonName << "!" << endl;
      cout << currentPokemon->name << " has leveled up to level " << currentPokemon->level << "." << endl;
      return true;
   }
   else
   {
      cout << endl << "Shayon Gupta and " << shayonPokemonName << "have defeated you." << endl;
      cout << "You have been transported to the local Pokémon Center." << endl;
      pokemonCenter();
      return false;
   }
}

void pokemonCenterHelper(Pokemon* p)
{
   if (p == NULL)
      return;
   pokemonCenterHelper(p->left);
   p->currentHP = p->hp;
   pokemonCenterHelper(p->right);
}

void Game::pokemonCenter()
{
   Pokemon *p = pokeTree.root;
   pokemonCenterHelper(p);
   cout << endl << "The health of your Pokémon has been fully restored." << endl;
   printPokemon();
}

int Game::getNumPokemon(Pokemon* p)
{
   if (p == NULL)
      return 0;
   return 1 + getNumPokemon(p->left) + getNumPokemon(p->right);
}

void Game::gameStatus()
{
   City *currentCity = getCurrentCity();
   int numPokemon = getNumPokemon(pokeTree.root);
   cout << endl << "*********************************" << endl
                << "*  Current City: " << currentCity->cityName << "\t*" << endl
                << "*  Coins: " << numCoins << "\t\t\t*" << endl
                << "*  Pokemon Collected: " << numPokemon << "\t\t*" << endl
                << "*  PokéBalls: " << numPokeBalls << "\t\t\t*" << endl
                << "*********************************" << endl;
}

void Game::displayMenu()
{
   City *currentCity = getCurrentCity();
   if (currentCity->cityName != "Shayon City")
   {
      cout << endl << "======Main Menu======" << endl
           << "1. Travel" << endl
           << "2. Battle" << endl
           << "3. See Pokémon" << endl
           << "4. Go to PokéMart" << endl
           << "5. Go to Pokémon Center" << endl
           << "6. Quit" << endl;
   }
   else
   {
      cout << endl << "======Main Menu======" << endl
           << "1. Travel" << endl
           << "2. Battle" << endl
           << "3. See Pokémon" << endl
           << "4. Go to PokéMart" << endl
           << "5. Go to Pokémon Center" << endl
           << "6. Quit" << endl
           << "999. BATTLE SHAYON!!!" << endl;
   }
}

int main()
{
   Game game; // game initialization
   vector<string> cityNames;
   ifstream file("cities.txt");
   if (file.is_open())
   {
      string line, city, distance; // declaration of string variables
      getline(file, line);
      stringstream ss(line);
      while (getline(ss, city, ','))
      {
         if (city != "cities")
         {
            game.addCity(city); // adds all cities
            cityNames.push_back(city);
         }
      }
      int row = 0;
      while (getline(file, line)) // goes through text file line by line and adds all edges
      {
         // cout << line << endl;
         for (unsigned int i = 0; i < line.length(); i++) // removes city name from beginning of line
         {
            if (line[i] == ',')
            {
               line = line.substr(i + 1);
               break;
            }
         }
         stringstream ss1(line);
         int col = 0;
         while (getline(ss1, distance, ',')) // adds edges
         {
            if (stoi(distance) > 0)
            {
               // cout << " ... Reading in " << cityNames[row] << " -- " << cityNames[col] << " -- " << distance << endl;
               game.addEdge(cityNames[row], cityNames[col], stoi(distance)); // adds all edges
            }
            col++;
         }
         row++;
      }
   }
   cout << " " << endl;
   game.intro();
   game.chooseStarter();

   bool quit = false, win = false;
   string strInput;
   int input;
   while (!quit && !win)
   {
      game.displayMenu();
      getline(cin, strInput);
      input = stoi(strInput);
      switch (input)
      {
         case 1:
         {
            game.travelMenu();
            break;
         }
         case 2:
         {
            game.battle();
            break;
         }
         case 3:
         {
            game.printPokemon();
            break;
         }
         case 4:
         {
            game.pokeMart();
            break;
         }
         case 5:
         {
            game.pokemonCenter();
            break;
         }
         case 6:
         {
            cout << endl << "Goodbye! Thanks for playing!" << endl << endl;
            quit = true;
            break;
         }
         case 999:
         {
            win = game.shayonGym();
            if (win)
               cout << "He has crowned you the new king of Data Structures!" << endl;
            break;
         }
      }
   }
}
