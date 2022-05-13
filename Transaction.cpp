#include "transaction.h"

// default constructor.  Uses empty string for name, entrance time 1,
// transaction time 1
Transaction::Transaction(){
  my_transaction_name = "";

  my_transaction_time = 1;
  
  my_entry_time = 0;
}

void Transaction::Set_Name(string n){
  my_transaction_name = n;
}



void Transaction::Set_Transaction_Time(int t){
  my_transaction_time = t;
}

void Transaction::Set_Entry_Time(int t)
{
	my_entry_time = t;
}


string Transaction::Get_Name() const{
  return my_transaction_name;
}



int Transaction::Get_Transaction_Time() const{
  return my_transaction_time;
}

int Transaction::Get_Entry_Time() const
{
	return my_entry_time;
}

bool Transaction::operator==(const Transaction& other) const{
  if(Get_Entry_Time() == other.Get_Entry_Time())
    return true;
  else
    return false;
}

bool Transaction::operator!=(const Transaction& other) const{
  if(Get_Entry_Time() != other.Get_Entry_Time())
    return true;
  else
    return false;
}

bool Transaction::operator<(const Transaction& other) const{
  if(Get_Entry_Time() < other.Get_Entry_Time())
    return true;
  else
    return false;
}

bool Transaction::operator<=(const Transaction& other) const{
  if(Get_Entry_Time() <= other.Get_Entry_Time())
    return true;
  else
    return false;
}