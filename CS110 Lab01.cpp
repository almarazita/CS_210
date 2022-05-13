//
// This is an example program for CS110 Lab 1.
//

#include <iostream>


using namespace std;

int main() {

//This program implements a small multiplication table
cout << "Please Enter a Number:";
int number;
cin >> number;

int TwoNumber = 2*number;
int ThreeNumber = 3*number;
int FourNumber = 4*number;
int FiveNumber = 5*number;

cout << number << " * 1 = " << number << endl;
cout << number << " * 2 = " << TwoNumber << endl;
cout << number << " * 3 = " << ThreeNumber << endl;
cout << number << " * 4 = " << FourNumber << endl;
cout << number << " * 5 = " << FiveNumber << endl;


return 0;
}
