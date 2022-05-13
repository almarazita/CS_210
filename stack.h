#ifndef STACK_H
#define STACK_H

#include "node.h"
template <typename T>
class Stack{
 public:
  // default constructor- creates an empty stack
  Stack();

  // Copy Constructor- creates a copy of a stack given as a parameter
  Stack(const Stack<T>& S);
  // destructor- destorys stack and all nodes
  ~Stack();

  
  // Push a new item onto the stack
  void Push(const T& new_val);

  // Pop the top item off of the stack
  T Pop();

  // return the top item from the stack
  T Inspect_Top();

  // returns true if stack has 0 elements, false otherwise
  bool Is_Empty();
  
  // returns the number of elements in the stack
  
  // returns true if the last operation caused an error, false otherwise
  bool Error() const;

  // = operator.  Used to make a deep copy when we assign one stack to another
  Stack<T>& operator=(const Stack<T>& other);

 private:
  // pointer to the top of the stack
  Node<T>* Top;

  // boolean that keeps track of whether the last operation caused an error
  bool last_error;
};
// Constructor: creates a new, empty stack
template <typename T>
Stack<T>::Stack(){
  Top=NULL;
  last_error= false;
}


// Copy constructor- works a lot like the copy constructor for list
template <typename T>
Stack<T>::Stack(const Stack& S){
  // check for empty stack
  if(S.Top == NULL)
    Top = NULL;
  else{
    Top = new Node<T>;
    Top->set_item(S.Top->get_item());
    Node<T>* p = Top;
    Node<T>* other_p = S.Top->get_next();
    while(other_p != NULL){
      Node<T>* new_node = new Node<T>;
      new_node->set_item(other_p->get_item());
      p->set_next(new_node);
      p = p->get_next();
      other_p = other_p->get_next();
    }
    p->set_next(NULL);
  }
}

// Destructor: removes and deletes all nodes from the stack
template <typename T>
Stack<T>::~Stack(){
  while(!Is_Empty()){
    int x = Pop();
  }
  Top=NULL;
  last_error = false;
}

// Pushes an item onto the stack- making it the new stack top.
// O(1)
template <typename T>
void Stack<T>::Push(const T&new_val){
  Node<T>* new_top = new Node<T>;
  new_top->set_item(new_val);
  new_top->set_next(Top);
  Top = new_top;
  last_error = false;
}

// Deletes the top item from the stack and returns its value.  If the stack is empty,
// returns -1 and sets the error condition
template <typename T>
T Stack<T>::Pop(){
  if(Is_Empty()){
    last_error = true;
    return T();
  }
  else{
    Node<T>*kill = Top;
    Top = Top->get_next();
    kill->set_next(NULL);
    T popped_val = kill->get_item();
    delete kill;
    last_error = false;
    return popped_val;
  }
}

// Returns the value in the top node of the stack
// Functionally equivalent to popping the item, then pushing it back
template <typename T>
T Stack<T>::Inspect_Top(){
  if(Is_Empty()){
    last_error = true;
    return T();
  }
  else{
    last_error = false;
    return Top->get_item();
  }
}

// returns true if the stack is empty (which happens when the top s null), false otherwise
template <typename T>
bool Stack<T>::Is_Empty(){
  last_error = false;
  return (Top==NULL);
}

// returns the error value- was the last operation an error?
// Errors can only happen if we do a Pop or Top on an empty stack
template <typename T>
  bool Stack<T>::Error() const{
  return last_error;
}
 
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs){
  // check for self-assignment
  if(this == &rhs)
    return *this;
  else{
    // delete the old nodes from our stack
    while(!Is_Empty())
      Pop();
    // copy elements from rhs
    if(rhs.Top == NULL)
      Top = NULL;
    else{
      Top = new Node<T>;
      Top->set_item(rhs.Top->get_item());
      Node<T>* p = Top;
      Node<T>* other_p = rhs.Top->get_next();
      while(other_p != NULL){
	Node<T>* new_node = new Node<T>;
	new_node->set_item(other_p->get_item());
	p->set_next(new_node);
	p = p->get_next();
	other_p = other_p->get_next();
      }
      p->set_next(NULL);
    }
    return *this;
  }
}
  
#endif
