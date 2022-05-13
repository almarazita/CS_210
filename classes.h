#ifndef CLASSES_H
#define CLASSES_H
#include <string>

using namespace std;

class Talkative{
  // an abstract base class defines an interface.  In this case, it 
  // states that all derived classes need to overload the "speak" function
  private:
	string name;
  
 public:
  virtual void Speak() = 0; // =0 means "purely virtual", 
                           // so no objects of type "abstract" can be created

  virtual void Greet(); // "greet" will have an implementation, 
                        // so derived classes can use this implementation
  
  void setName(string n);
  
  string getName();
  
}; // end of class definition



class Apathetic: public Talkative{
  // "apathetic" is a class that inherits from talkative  
 public:
  virtual void Speak(); // _not_ =0, because we want to implement this function
                        // and have apathetic objects
};

class Excited: public Talkative{
  // "excited" is another class that inherits from talkative.  It implements
  // "speak", overloads "greet", and writes its own "BeExcited" function
 public:
  virtual void Speak();
  virtual void Greet();
  virtual void BeExcited();
};

class Manic: public Excited{
  // "Manic" derives from Excited.  It gets all of the "excited" functions 
  // for free, and re-implements "BeExcited", because apparently it wasn't
  // exciting enough
 public:
  virtual void BeExcited();
};

class Angry: public Talkative
{
	public:
		virtual void Speak();
};

class Raging: public Angry
{
	public:
		virtual void Speak();
};

#endif