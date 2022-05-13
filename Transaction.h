// class that defines a tranaction as a name, an enter time, and an
// amount of time to perform the transaction
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>

using namespace std;

class Transaction{
 public:
  // default constructor.  Uses empty string for name, entrance time 1,
  // transaction time 1
  Transaction();

  void Set_Name(string n);
 
  void Set_Transaction_Time(int t);
  
  void Set_Entry_Time(int t);

  string Get_Name() const;

  int Get_Transaction_Time() const;
  
  int Get_Entry_Time() const;
  
  bool operator==(const Transaction& other) const;
  
  bool operator!=(const Transaction& other) const;
  
  bool operator<(const Transaction& other) const;
  
  bool operator<=(const Transaction& other) const;

 private:
  string my_transaction_name;

  int my_transaction_time;
  
  int my_entry_time;
};

#endif