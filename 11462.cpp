#include <iostream>
#include <cstring>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  size_t ages[101], age, n;
  while (cin >> n) {
    if (!n) break;
    memset(ages, 0, sizeof(size_t) * 101);
    while (n--) {
      cin >> age;
      ++ages[age];
    }

    bool first = true;
    for (int i(1); i < 101; ++i) {
      while (ages[i]--) {
        if (!first)
          cout << " ";
        first = false;
        cout << i;
      }
    }
    cout << endl;
  }
  return 0;
}
