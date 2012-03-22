#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(void) {
  string word;
  while (cin >> word) {
    reverse(word.begin(), word.end());
    cout << word;
    if (cin.peek() == '\n') cout << endl;
    else cout << " ";
  }
}
