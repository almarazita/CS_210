#include <iostream>
#include <vector>
using namespace std;

//Iterative Solution
// Pre: n is a positive integer
//  "max_factor" is a positive integer <= n
// Post: outputs to the screen all numbers <= max_factor that divide evenly into n.
void Print_Divisors(int n, int max_factor)
{
  for(int i = max_factor; i > 0; i--)
  {
    if(n%i==0)
      cout << " " << i << " ";
  }
}

//Recursive Solution
void Recur_Print_Divisors(int n, int max_factor)
{
  if(max_factor > 0)
  {
    if(n%max_factor == 0)
      cout << " " << max_factor << " ";
    Recur_Print_Divisors(n, max_factor-1);
  }
}

int main()
{
  int num, factor;
  cout << "Enter a number: ";
  cin >> num;
  cout << "Enter a number less than or equal to " << num << ": ";
  cin >> factor;
  cout << "The divisors of " << num << " <= " << factor << " are\n";
  Print_Divisors(num, factor);
  cout << "\nusing iteration and\n";
  Recur_Print_Divisors(num, factor);
  cout << "\nusing recursion.\n";
  return 0;
}