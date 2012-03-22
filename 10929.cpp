#include <iostream>
#include <numeric>

using namespace std;

int diff_odd_even(int sum, int number)
{
  static int sign = 0;
  sign = !sign;
  return (sign ? sum + number - '0': sum - number + '0');
}

int main()
{
  ios::sync_with_stdio(false);
  string word;
  while (cin >> word) {
    if (word == "0") break;
    int diff = accumulate(word.begin(), word.end(), 0, diff_odd_even);
    if (diff % 11)
      cout << word << " is not a multiple of 11." << endl;
    else
      cout << word << " is a multiple of 11." << endl;
  }
  return 0;
}
