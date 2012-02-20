#include <iostream>
#include <cstdlib>
#include <string.h>

using namespace std;

int number_map[3000];

int main(void)
{
  ios::sync_with_stdio(false);
  int n;
  while (cin >> n) {
    bool jolly = true;
    memset(number_map, 0, 3000 * sizeof(int));
    long curr, prev;
    cin >> prev;
    for (int i = 1; i < n; ++i) {
      if (!jolly) {
        cin.ignore(2000000, '\n');
        break;
      }
      cin >> curr;
      long diff = abs(curr - prev);
      prev = curr;
      if (diff > (n-1)) {
        jolly = false;
        continue;
      }
      if (number_map[diff]) {
        jolly = false;
        continue;
      }
      number_map[diff] = 1;
    }

    if (jolly)
      cout << "Jolly" << endl;
    else
      cout << "Not jolly" << endl;
  }
}
