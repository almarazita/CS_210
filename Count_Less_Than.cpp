#include <iostream>
#include <vector>
using namespace std;

//Iterative solution
// Pre: "v" is a vector of integers
//  "key" is any integer
//  "start" is a position in v
// Post: Returns the number of elements from v[start]// to v[v.size()-1] that are < "key"
int Count_Less_Than(const vector<int>& v, int key, int start)
{
  int count = 0;
  for(int i = start; i<v.size(); i++)
  {
    if(v[i] < key)
      count++;
  }
  return count;
}

//Recursive solution
int Recur_Count_Less_Than(const vector<int>& v, int key, int start)
{
  if(start >= v.size())
    return 0;
  if(v[start] < key)
    return 1 + Recur_Count_Less_Than(v, key, start+1);
  else
    return Recur_Count_Less_Than(v, key, start+1);
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
  int key;
  cout << "Enter a number: ";
  cin >> key;
  cout << "There are " << Count_Less_Than(v, key, start) << " elements in your vector from position " << start << " to position " << len-1 << " that are less than " << key << ". Using recursion, there are " << Recur_Count_Less_Than(v, key, start) << ".\n";
}