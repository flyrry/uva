#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
  int n;
  while (cin >> n) {
    int counter = 1;
    int temp = 1;

    while (temp % n) {
      if (temp < n) {
        temp = temp * 10 + 1;
        ++counter;
      }
      else {
        temp %= n;
      }
    }
    cout << counter << endl;
  }
  return 0;
}

