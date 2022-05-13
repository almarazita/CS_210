// Sean McCulloch
// 3/25/15
// List.h
// Implementes a sorted linked list using the node class defined in
// node.h and node.cpp.  This class will have member functions
// for insertion, deletion, and printing the list elements out.
// Note that since this list keeps its notdes in sorted order, it's important
// that the type of the nodes be something we can compare with operators like <

#ifndef LIST_H
#define LIST_H

#include "Node.h"
#include <iostream>
#include <cstdlib>

using namespace std;

template <typename T>
class List{
  public:
	// constructor- creates an empty list
	List();
	//destructor- deletes the entire list, freeing every node.
	~List();
	
	// copy constructor- called so that we have a "deep copy"
	// of the list when needed.
	List(const List<T>& L);
	
	// Print the elements of the list
	void Print_List() const;
	
	// other member functions- to be done in lab
	
	// inserts an element into the correct sorted position of
	// the list
	void Insert(const T& new_item);
	
	// deletes an item from the list, if it's there.  Returns
	// true if the item was deleted, false otherwise
	bool Delete(const T& del_item);
	
	//find_item returns the index of the item if it is in
	// the list, -1 otherwise
	int Find_Item(const T& item);
	
	//find_item_at_index returns the item at position index in
	// the reference parameter "value". The first item is at index 1.
	// Returns true if the index
	// is a valid one, false otherwise
	bool Find_Item_At_Index(int position, T& value);
	
	// This function computes the size of the list.  It will
	// count every node (an O(n) operation).  We could make 
	// this constant time by storing the size in the class, but
	// that would require constant updating in our insert and 
	// delete functions
	int Size() const;
	
  private:
  	//the only data we need in the private section is a pointer to the list
  	Node<T>* theList;
};

// The default constructor creates a list with no elements
template <typename T>
List<T>::List(){
	theList = NULL; // so that we have a consistent way to 
	                // check for an empty list
}

// the list destructor has to delete the whole list, node by node
template <typename T>
List<T>::~List(){
	Node<T>* p = theList;
	Node<T>* kill = theList;
	while(p!= NULL){
		kill = p;
		p = p->get_next();
		delete kill;
	}
	theList = NULL; // just in case
}

// the list copy constructor creates a new list with new nodes,
// all with identical data to those in the list we're copying
// from
template <typename T>
List<T>::List(const List<T>& L){
	Node<T>* orig_list_pos = L.theList; // holds the position of
	                                 // the thing we're copying
	                                 // in L
	if(orig_list_pos == NULL) // then L is empty..
	  theList = NULL; //...and so are we
	else{
	  theList = new Node<T>;
	  theList->set_item(orig_list_pos->get_item());
	  Node<T>* new_list_end= theList; // points to the last item in the
	                      // list we're creating
	  orig_list_pos = orig_list_pos->get_next();
	  
	  // this loop will continually copy items from the original
	  // list (pointed at by "orig_list_pos") to the new list
	  // (whose last item is pointed at by "new_list_end"), until
	  // the oringinal list runs out of elements
	  while(orig_list_pos != NULL) {
	  	// the loop has 2 parts.  First, we create the new node,
	  	// and set it's value
	  	
	  	Node<T>* n = new Node<T>;
	  	n->set_item(orig_list_pos->get_item());
	  	n->set_next(NULL);
	  	new_list_end->set_next(n); // links n into the list
	  	
	  	// now, we set up the next iteration
	  	new_list_end = n; //so it points to the last element in
	  	                   // the new list again
	  	orig_list_pos = orig_list_pos->get_next();
	  }
	  
	  // when we leave the loop, we have a whole new copy, 
	  // pointed at by theList.  The only thing we have to do
	  // is set the last element to point to NULL.
	  new_list_end->set_next(NULL);
	}
}
	  

// the print_list function prints all of the elements in the
// list
template <typename T>
void List<T>::Print_List() const{

	Node<T>* p = theList;
	while(p != NULL){
	  cout << p->get_item() << " ";
	  p = p->get_next();
	 }
}


// These functions are to be done in lab.  Uncomment the
// prototype when you're working on them

// Insert inserts an element into the appropriate place in the
// sorted list
template <typename T> 
void List<T>::Insert(const T& new_item)
{
	// Make a node for the new item
	Node<T>* new_guy = new Node<T>;
	new_guy->set_item(new_item);
	new_guy->set_next(NULL); // Just in case
	
	// Case 1: The list is empty
	if(theList == NULL)
	{
		theList = new_guy; // The new item is the first and only item in the list
	}
	
	// Case 2: The new node belongs first
	else
	{
		if(new_item <= theList->get_item())
		{
			new_guy->set_next(theList);
			theList = new_guy; // New item is the new head
		}
		
		// Case 3: The new node belongs in the middle; if it belongs at the end, the next field will be set to NULL
		else
		{
			Node<T>* prevPtr = theList;
			Node<T>* curPtr = theList->get_next(); // Move two pointers in lockstep
			while(curPtr != NULL && curPtr->get_item() < new_item) // Stops at the first item that's too big
			{
				prevPtr = curPtr;
				curPtr = curPtr->get_next();
			}
			new_guy->set_next(curPtr); // Set next field to the first big item, and don't lose the chain
			prevPtr->set_next(new_guy);
		}
	}	
}
 

// Delete removes an item from the list.  returns true if the
// item was successfully deleted, false if it wasn't (becuase
// the item couldn't be found)
template <typename T>
bool List<T>::Delete(const T& del_item)
{
	// Case 1: The list is empty
	if(theList == NULL)
	{
		return false;
	}
	
	// Case 2: The item to delete is the first item in the list
	if(theList->get_item() == del_item)
	{
		Node<T>* kill = theList; // Mark it for death
		theList = theList->get_next(); // The next item is the new head
		kill->set_next(NULL); // Detach from the list
		delete kill;
		kill = NULL; // Safe practice
		return true;
	}
	
	// Case 3: The item to delete is in the middle of the list
	else
	{
		Node<T>* before = theList;
		Node<T>* target = theList->get_next(); // Two pointers move in lockstep
		while(target != NULL && target->get_item() != del_item) // Stops at the item to be deleted
		{
			before = target;
			target = target->get_next();
		}
		if(target == NULL) // The item is not in the list
		{
			return false;
		}
		Node<T>* after = target->get_next();
		before->set_next(after); // Connect the previous node to the one after the one to be deleted
		target->set_next(NULL); // Detach from the list
		delete target; // And kill it
		target = NULL;
		return true;
	}
}


//find_item returns the index of the item if it is in the list,
// -1 otherwise.  It uses a sequential search technique
template <typename T>
int List<T>::Find_Item(const T& item)
{
	Node<T>* ptr = theList;
	int pos = 1;
	while(ptr->get_item() != item && ptr != NULL)
	{
		ptr = ptr->get_next();
		pos++;
	}
	if(ptr == NULL) // Item not found
	{
		return -1;
	}
	else
	{
		return pos;
	}
}

//find_item_at_index returns the item at position index in
// the reference parameter "value". The first item is at index 1. 
// The last item is at index Size().
// Returns true if the index
// is a valid one, false otherwise
template <typename T>
bool List<T>::Find_Item_At_Index(int position, T& value)
{
	if(position >= 1 && position <= Size()) // Within the number of items in the list
	{
		Node<T>* ptr = theList;
		for(int pos = 1; pos < position; pos++) // Until we reach the given position
		{
			ptr = ptr->get_next();
		}
		value = ptr->get_item(); // Copy index into reference parameter
		return true;
	}
	else
	{
		return false;
	}
}

// this function computes the size of the list.  It will
	// count every node (an O(n) operation).  We could make 
	// this constant time by storing the size in the class, but
	// that would require constant updating in our insert and 
	// delete functions
template <typename T>
int List<T>::Size() const
{
	int size = 0;
	if(theList != NULL)
	{
		Node<T>* ptr = theList;
		while(ptr != NULL) // Loop through chain to count nodes
		{
			size++;
			ptr = ptr->get_next();
		}
	}
	return size;
}

#endif
