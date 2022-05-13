#include <iostream>
#include <vector>
using namespace std;

//Iterative solution
// Pre: "v" is a vector of integers
//  "start" and "end" are positions in v
// Post: returns v[start] + v[start+1] + ... + v[end]
int Add_Between(const vector<int>& v, int start, int end)
{
  int sum = 0;
  for(int i = start; i <= end; i++)
  {
    sum += v[i];
  }
  return sum;
}

//Recursive solution
int Recur_Add_Between(const vector<int>& v, int start, int end)
{
  if(start == end) // base case: length is 1
  {
    return v[start];
  }
  else
  {
    return v[start] + Recur_Add_Between(v, start+1, end);
  }
}

int main()
{
  vector<int> v;
  int len = 0;
  cout << "What is the size of your vector?\n";
  cin >> len;
  for(int i = 0; i < len; i++)
  {
    int x;
    cout << "Enter integer at position " << i << ": ";
    cin >> x;
    v.push_back(x);
  }
  int start = 0;
  cout << "Enter starting position (0-" << len-1 << "): ";
  cin >> start;
  int end = 9;
  cout << "Enter ending position (0-" << len-1 << "): ";
  cin >> end;
  cout << "The sum of elements from " << start << " to " << end << " is " << Add_Between(v, start, end) << " using iteration and " << Recur_Add_Between(v, start, end) << " using recursion.\n";
  return 0;
}