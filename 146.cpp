#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  string code, initial_code;
  while (cin >> code) {
    if (code == "#")
      break;

    initial_code = code;
    next_permutation(code.begin(), code.end());
    if (lexicographical_compare(initial_code.begin(), initial_code.end(), code.begin(), code.end())) 
      cout << code << endl;
    else
      cout << "No Successor" << endl;
  }
  return 0;
}
