#include "Monster.h"
#include <iostream>
#include <string>

using namespace std;

Monster::Monster(string name)
{
	my_name = name;
	my_health = 100;
	my_power = 1;
	my_toughness = 1;
	am_alive = true;
}

void Monster::Set_Power(int p)
{
	if(p > 0)
		my_power = p;
	else
		my_power = 1;
}

void Monster::Set_Toughness(int t)
{
	if(t > 0)
		my_toughness = t;
	else
		my_toughness = 1;
}

void Monster::Set_Name(string new_name)
{
	my_name = new_name;
}

string Monster::Get_Name()
{
	return my_name;
}

int Monster::Get_Power()
{
	return my_power;
}

int Monster::Get_Toughness()
{
	return my_toughness;
}

int Monster::Get_Health()
{
	return my_health;
}

bool Monster::Is_Living()
{
	return am_alive;
}

void Monster::Display()
{
	if(am_alive)
		cout << "LIVING\n";
	else
		cout << "DEAD\n";
	cout << "Monster name: " << Get_Name() << endl << "Health: " << Get_Health() << endl << "Power: " << Get_Power() << endl << "Toughness: " << Get_Toughness() << endl;
}

void Monster::Receive_Damage(int damage)
{
	if(damage > 0)
	{
		if(damage >= Get_Health())
		{
			my_health = 0;
			am_alive = false;
		}
		else
			my_health -= damage;
	}
}

void Monster::Fight(Monster& other)
{
	int attack = 0;
	int damage = 0;
	if(Is_Living())
	{
		attack = Get_Power() - other.Get_Toughness();
	}
	if(other.Is_Living())
	{
		damage = other.Get_Power() - Get_Toughness();
	}
	other.Receive_Damage(attack);
	Receive_Damage(damage);
	cout << "The monsters fought.\n";
}

void Monster::Heal(int amount)
{
	if(!Is_Living())
	{
		if(0 < amount && amount <= 100)
		{
			am_alive = true;
			my_health = amount;
		}
		else if(amount > 100)
		{
			am_alive = true;
			my_health = 100;
		}
	}
	else
	{
		if(0 < amount && amount + Get_Health() <= 100)
		{
			my_health += amount;
		}
		else if(amount > 100)
		{
			my_health = 100;
		}
	}
}