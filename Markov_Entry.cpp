#include "Markov_Entry.h"
#include <iostream>
#include <string>
#include "bag.h"

using namespace std;

Markov_Entry::Markov_Entry()
{
	word = "";
	Bag<string> successors;
}

Markov_Entry::Markov_Entry(string s)
{
	setWord(s);
	Bag<string> successors;
}

string Markov_Entry::getWord() const
{
	return word;
}

int Markov_Entry::frequency() const
{
  return successors.size();
}

void Markov_Entry::setWord(const string& s)
{
	word = s;
}

void Markov_Entry::addSuccessor(const string& s)
{
	successors.insert(s);
}

int Markov_Entry::getFrequencyOf(const string& s) const
{
	return successors.count(s);
}

void Markov_Entry::display() const
{
	cout << "Word: " << word << endl;
	cout << "Successors: ";
  successors.Display();
}

bool Markov_Entry::contains(const string& s)
{
	return successors.count(s) > 0;
}

bool Markov_Entry::removeSuccessor(const string& s)
{
	return successors.remove(s);
}

void Markov_Entry::clear()
{
  string item = "";
  while(!successors.is_empty())
    {
      successors.choose(item);
      successors.remove(item);
    }
}

string Markov_Entry::chooseSuccessor() const
{
	string s = "";
  successors.choose(s);
  return s;
}

bool Markov_Entry::isEqual(const Markov_Entry& other) const
{
	return getWord() == other.getWord();
}