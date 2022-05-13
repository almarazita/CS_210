#include <iostream>
#include <vector>
using namespace std;

//Iterative solution
// Pre: "s" is any string whose characters are all // in the same case
//  "start" is a position in s
// Post: returns true if
//  s[start] <= s[start+1] <= ... <= s[s.size()-1]
//  returns false otherwise.
bool Is_Alphabetical(const string& s, int start)
{
  for(int i = start; i < s.length()-1; i++)
  {
    if(s[i] > s[i+1])
      return false;
  }
  return true;
}

//Recursive solution
bool Recur_Is_Alphabetical(const string& s, int start)
{
  if(start == s.length()-1)
    return true;
  if(s[start] > s[start+1])
    return false;
  return Recur_Is_Alphabetical(s, start+1);
}

int main()
{
  string word;
  cout << "Enter a word (all upper or lowercase): ";
  cin >> word;
  int start;
  cout << "Enter a starting position in " << word << ": ";
  cin >> start;
  if(Is_Alphabetical(word, start))
    cout << word << " is alphabetical starting at position " << start << " using iteration and ";
  else
    cout << word << " is not alphabetical starting at position " << start << " using iteration and ";
  if(Recur_Is_Alphabetical(word, start))
    cout << "is alphabetical using recursion.\n";
  else
    cout << "is not alphabetical using recursion.\n";
  return 0;
}