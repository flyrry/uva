#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  size_t cases;
  cin >> cases;
  while (cases--) {
    string word;
    cin >> word;
    sort(word.begin(), word.end());
    cout << word << endl;
    while (next_permutation(word.begin(), word.end())) cout << word << endl;
    cout << endl;
  }
  return 0;
}
