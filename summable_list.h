#ifndef SUMMABLE_LIST_
#define SUMMABLE_LIST_
#include <cstdlib>
#include "List.h"

// Extends List<T>, a sorted linked list ADT, to add all elements.
template <typename T>
class Summable_List: public List<T>
{
	public:
		T Sum() const;
};

// Returns the sum of all elements in the list.
// Does not compile on types that can't be added.
template <typename T>
T Summable_List<T>::Sum() const
{
	T total = T();
	
	/* O(N^2) version using inherited public member functions
	T item = T();
	for(int i = 0; i < List<T>::Size(); i++) // Make namespace explicit
	{
		if(List<T>::Find_Item_At_Index(i, item)) // Returns boolean, copies into reference parameter
			total += item;
	}*/
	
	// O(N) version using a protected member to access the head pointer
	Node<T>* ptr = List<T>::Get_Front();
	while(ptr != NULL) // Stops at the end
	{
		total += ptr->get_item();
		ptr = ptr->get_next(); // Increment
	}
	
	return total;
}

#endif