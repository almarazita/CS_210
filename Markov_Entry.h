#ifndef MARKOV_ENTRY_
#define MARKOV_ENTRY_

#include <string>
#include "bag.h"

using namespace std;

class Markov_Entry
{
	private:
		string word;
		Bag<string> successors;
	
	public:
		// Default constructor
		Markov_Entry();
		
		// Parameterized constructor
		Markov_Entry(string s);
		
		// Getters
		// Returns the value of the word.
		string getWord() const;
		// Returns the number of successors the word has (the number of times the word appears).
		int frequency() const;
		
		// Mutators
		// Changes the value of the word.
		void setWord(const string& s);
		// Adds a successor to the word.
		void addSuccessor(const string& s);
		// Removes a given successor from the word if it is there, returning true if successful, and false otherwise.
		bool removeSuccessor(const string& s);
		// Removes all successors from the word.
		void clear();
		
		// Facilitators
		// Returns true if the given word is a successor, and false otherwise.
		bool contains(const string& s);
		// Returns the number of times a given word appears as a successor.
		int getFrequencyOf(const string& s) const;
		// Returns one of the word's successors at random (uses the bag class choose function).
		string chooseSuccessor() const;
		// Returns true if the word is identical to another word, false otherwise.
		bool isEqual(const Markov_Entry& other) const;
		// Outputs the word and its successors to the screen.
		void display() const;
};

#endif