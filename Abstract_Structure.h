#ifndef ABSTRACT_STRUCTURE_
#define ABSTRACT_STRUCTURE_

// Abstract template base class that data structures inherit from to make hierarchy explicit
// Declares common operations size and is empty
template <typename T>
class Abstract_Structure
{
	public:
		// Purely virtual and must be defined and overloaded in the derived class
	
		// Tests to see whether the structure holds data, returns true if empty
		virtual bool Is_Empty() const = 0;
		
		// Returns the number of items stored in the data structure
		virtual int Size() const = 0;
};

/* Stubbed Is_Empty() function defined to return true until overloaded
template<typename T>
bool Abstract_Structure<T>::Is_Empty() const
{
	return true;
}

// Stubbed Size() function defined to return zero until overloaded
template<typename T>
int Abstract_Structure<T>::Size() const
{
	return 0;
}*/

#endif