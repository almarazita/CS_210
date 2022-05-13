#include <iostream>
#include <string>
#include "classes.h"

using namespace std;

// The talkative class implements the greet function.  It does _not_ implement
// the "speak" function, because it's purely virtual

void Talkative::Greet(){
  cout << "Hello. My name is " << getName();
}

void Talkative::setName(string n)
{
	name = n;
}

string Talkative::getName()
{
	return name;
}

// the apathetic derived class  will implement Speak, and use the 
// default version of "greet" in the base class
  void Apathetic::Speak(){
  Greet(); // call the "greet" function we get from the base class
  cout << ". " << endl;
  cout << "It's an ok day, I guess.  Whatever.  Who cares?" << endl;
}

// the excited derived class will over-ride the default "greet" function:
void Excited:: Greet(){
  // just to show you that we can do it, here's how we call the Talkative 
  // version of "Greet".  Notice that this is _not_ a recursive call:
  Talkative::Greet();
  // now be excited:
  cout << "!";
}

// we have to implement the "Speak" function to be a derived class we can make objects of:
void Excited::Speak(){
  Greet(); // calls the _excited_ version of Greet
  cout << endl;
  cout << "What a great day it is today!! ";
  BeExcited();
  cout << endl;
}

// the BeExcited function outputs an appropriate level of excitement
void Excited::BeExcited(){
  cout << "Woo-hoo!";
}

// The "Manic" class will use the Excited class as a base class, and derive from _it_.  It will also
// overload the BeExcited function to be even more excited
void Manic::BeExcited(){
  for(int i = 0; i < 10; i++){
    cout << "Woo-HOO!!!!! ";
  }
}
  
// Angry inherits from Talkative to give an angry Speak message
void Angry::Speak()
{
	Greet();
	cout << endl << ">:(" << endl;
	cout << "I don't like you." << endl;
}

// Raging inherits from Angry to give a really angry Speak message
void Raging::Speak()
{
	Greet();
	cout << endl << ">:(" << endl;
	cout << "I hate you!" << endl;
}
