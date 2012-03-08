#include <iostream>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  long long a, l;
  size_t i = 0, t;
  while (cin >> a >> l) {
    if (a < 0 && l < 0)
      break;
    ++i;
    cout << "Case " << i << ": A = " << a << ", limit = " << l << ", number of terms = ";
    t = 0;
    while (a <= l) {
      ++t;
      if (a == 1) break;
      a = (a % 2) ? (a * 3 + 1) : (a / 2);
    }
    cout << t << endl;
  }
  return 0;
}
