#ifndef MONSTER_H
#define MONSTER_H

#include <string>
using namespace std;

class Monster{
 public:
  // constructor, can provide a name as a parameter
  Monster(string name = "Nameless");

  // sets power to p, unless p <= 0.  In that case, sets power to 1
  void Set_Power(int p);
  // sets toughness to t, unless t <= 0.  In that case, sets toughness to 1
  void Set_Toughness(int t);
  // sets the name to "new_name"
  void Set_Name(string new_name);

  // Accessor functions to get the various attributes
  string Get_Name();
  int Get_Power();
  int Get_Toughness();
  int Get_Health();
  bool Is_Living();

  // Displays Monster info
  void Display();
  
  // Fights another monster  See assignment
  void Fight(Monster& other);

  // heals (and possibly brings back to life) the monster, up to a max
  // of 100 health
  void Heal(int amount);
  
 private:
  string my_name;
  int my_health;
  int my_power;
  int my_toughness;
  bool am_alive;
  // Helper function for Fight that decreases health and can change alive status
  void Receive_Damage(int damage);
};

    
#endif

  