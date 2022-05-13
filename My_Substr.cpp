#include <iostream>
#include <vector>
using namespace std;

//Iterative solution
// Pre: "s" is any string
//  "start" and "end" are positions in s
// Post: returns a string consisting of s[start]..s[end] (inclusive)
string My_Substr(const string& s, int start, int end)
{
  string substr = "";
  for(int i = start; i <= end; i++)
  {
    substr += s[i];
  }
  return substr;
}

//Recursive solution
string Recur_My_Substr(const string& s, int start, int end)
{
  if(start==end)
  {
    string a;
    a = s[end];
    return a;
  }
  return s[start] + Recur_My_Substr(s, start+1, end);
}

int main()
{
  string word;
  cout << "Enter a word: ";
  cin >> word;
  int start;
  cout << "Enter the starting position of your substring: ";
  cin >> start;
  int end;
  cout << "Enter the ending position of your substring: ";
  cin >> end;
  cout << "Your substring is " << My_Substr(word, start, end) << " using iteration and " << Recur_My_Substr(word, start, end) << " using recursion.\n";
}