#ifndef QUEUE_H
#define QUEUE_H

#include "doublenode.h"
#include <cstdlib>

template <typename T>
class Queue{
 public:
  //Constructor- creates an empty queue
  Queue();
  
  // Destructor- removes and deletes all nodes from the queue.
  // uncomment this when you have Dequeue and Is_Empty written
  ~Queue();

  // Copy constructor- makes a deep copy
  Queue(const Queue<T>& other);

  // enqueue- inserts an item into the back of the queue
  void Enqueue(const T& new_val);

  // dequeue- removes an item from the front of the queue
  // sets the error state if the queue is empty
  T Dequeue();

  // returns true if queue is empty
  bool Is_Empty();

  // returns true if the last operation caused an error- false otherwise
  bool Error() const;
 private:
  DoubleNode<T>* Front;
  DoubleNode<T>* Back;
  bool last_error;
};

// Default constructor- sets all pointers to NULL
template <typename T>
Queue<T>::Queue(){
  Front = NULL;
  Back = NULL;
}

// Copy constructor- makes a deep copy of the parameter
// Next points toward the front, and prev toward the back of the queue
template <typename T>
Queue<T>::Queue(const Queue<T>& other){
  if(other.Front == NULL){
    Front = NULL;
    Back = NULL;
  }
  else{
    Front = new  DoubleNode<T>;
    Front->set_item(other.Front->get_item());
    Front->set_next(NULL);
    DoubleNode<T>* p = Front;
    DoubleNode<T>* other_p = other.Front->get_prev();
    while(other_p != NULL){
      DoubleNode<T>* new_node = new DoubleNode<T>;
      new_node->set_item(other_p->get_item());
      p->set_prev(new_node);
      new_node->set_next(p);
      p = new_node;
      other_p = other_p->get_prev();
    }
    p->set_prev(NULL);
    Back = p;
  }

}

// destructor.  Commented out because it uses functions you'll write in the lab
template <typename T>
Queue<T>::~Queue(){
  while(!Is_Empty()){
    Dequeue();
  }
}

  // enqueue- inserts an item into the back of the queue
  template<typename T>
  void Queue<T>::Enqueue(const T& new_val)
  {
	  DoubleNode<T>* new_entry = new DoubleNode<T>; // Create new double node
	  new_entry->set_item(new_val); // New entry references new_val
	  new_entry->set_prev(NULL); // There's no one after them
	  
	  if(Is_Empty()) // Front and back are both NULL, new entry is new front and back
	  {
		  new_entry->set_next(NULL); // There's no one before them either (1-element queue)
		  Front = new_entry;
		  Back = new_entry;
	  }
	  
	  else // Inserted at the back of the queue (should work on 1-element list too)
	  {
		  new_entry->set_next(Back); // New back's next is old back
		  Back->set_prev(new_entry); // Old back's previous is new back
		  Back = new_entry; // Make new entry the new back
	  }
	  
	  last_error = false; // Set fail state
  }

  // dequeue- removes an item from the front of the queue
  // sets the error state if the queue is empty
  template<typename T>
  T Queue<T>::Dequeue()
  {
	  if(Is_Empty())
	  {
		  last_error = true;
		  return T();
	  }
	  else
	  {
		  T value = Front->get_item(); // Copy into return value
		  DoubleNode<T>* kill = Front; // Mark first entry for death
		  Front = Front->get_prev(); // Make the previous entry the new front
		  kill->set_prev(NULL); // Detach the first entry from the queue
		  if(Front != NULL) // If the list is not a one-node queue, detach the next pointer
			  Front->set_next(NULL);
		  else
			  Back = NULL; // One node in queue
		  delete kill; // Deallocate
		  kill = NULL; // Safe practice
		  last_error = false; // Set error state
		  return value;
	  }
  }

  // returns true if queue is empty
  template<typename T>
  bool Queue<T>::Is_Empty()
  {
	  return (Front == NULL && Back == NULL);
  }

#endif
