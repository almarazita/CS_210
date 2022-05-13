#include "player.h"
#include <string>

using namespace std;

// accessor functions
string Player::Get_Name() const
{
	return my_name;
}
 
int Player::Get_Pos() const
{
	return my_pos;
}

// mutator functions
void Player::Set_Name(const string& s)
{
	my_name = s;
}

void Player::Set_Pos(int new_pos)
{
	my_pos = new_pos;
}

// comparison operators- equality means the same name
bool Player::operator==(const Player& other) const{
  if(my_name == other.Get_Name())
    return true;
  else
    return false;
}

bool Player::operator!=(const Player& other) const{
  if(my_name != other.Get_Name())
    return true;
  else
    return false;
}

      
// < and <= means an earlier position
bool Player::operator<(const Player& other) const{
  if(my_pos < other.Get_Pos())
    return true;
  else
    return false;
}

bool Player::operator<=(const Player& other) const{
  if(my_pos <= other.Get_Pos())
    return true;
  else
    return false;
}
