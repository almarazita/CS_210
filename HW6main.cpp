#include <fstream>
#include "bag.h"
#include "Markov_Entry.h"
#include <iostream>
#include <string>

using namespace std;

// Open file
void openFile(ifstream& fin)
{
  string filename;
  cout << "Enter the filename: ";
	cin >> filename;
	fin.open(filename.data());
	while(!fin.is_open())
	{
		cout << "Illegal filename, try again: ";
		cin >> filename;
		fin.clear();
		fin.open(filename.data());
	}
}

// Write file into vector of Markov entries
vector<string> readFile(ifstream& fin)
{
  vector<string> file;
  string letters;
  while(!fin.eof())
  {
	  fin >> letters;
    file.push_back(letters);
  }
  return file;
}

// Makes a vector of Markov entries from the file
vector<Markov_Entry> makeEntries(vector<string>& v)
{
  vector<Markov_Entry> words(0); // Will hold Markov entries
  words.push_back(Markov_Entry(v[0])); // Add the first word
  int curIndex = 0; // Used to keep track of the correct entry to add successors to
  Markov_Entry temp; // Becomes the next Markov entry
  bool found; // To check if we already made an entry for it
  for(int i = 1; i < v.size(); i++) // Go through each word of the file
  {
    words[curIndex].addSuccessor(v[i]); // Add it as a successor to the previous word
    temp.setWord(v[i]); // Entry for current word
    found = false;
    for(int j = 0; j < words.size(); j++)
    {
      if(words[j].isEqual(temp)) // We already made an entry for it
      {
        found = true;
        curIndex = j; // So it adds the successor properly next iteration
      }
    }
    if(!found)
    {
      words.push_back(temp); // Add unique new entry
      curIndex = words.size() - 1;
    }
  }
  return words;
}

void generateString(vector<Markov_Entry>& entries)
{
  cout << "Enter the number of strings you would like to generate: ";
  int num;
  cin >> num;
  int index; // Keeps track of current entry to be outputted
  string next = "None"; // Chosen successor
	for(int count = 0; count < num; count++)
	{
		if(count == 0)
		{
			int rand = Draw(0, entries.size()-1);
      index = rand; // Pick a word to start
		}
    cout << entries[index].getWord() << " "; // Output to screen
    next = entries[index].chooseSuccessor(); // Find next word
    if(next == "")
    {
      index = Draw(0, entries.size() - 1); // If it's the last string, just choose a random word as its successor
    }
    else
    {
      for(int i = 0; i < entries.size(); i++)
      {
        if(entries[i].getWord() == next)
        {
          index = i; // Find the entry that corresponds to the chosen next word
        }
      }
    }
  }
}

int main()
{
  Init_RNG(-1);

  ifstream fin;
  openFile(fin);
  vector<string> file = readFile(fin);
  vector<Markov_Entry> entries = makeEntries(file);
  generateString(entries);
  
  return 0;
}