#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

#define N 50

int numbers[N];

inline int gcd(int a, int b) {
  if (a == b) return a;
  if (a < b) return gcd(a, b - a);
  return gcd(b, a - b);
}

int main()
{
  ios::sync_with_stdio(false);
  int n, num;
  while (cin >> n, n) {
    for (int i(0); i < n; ++i) {
      cin >> num;
      numbers[i] = num;
    }

    double pairs = 0, commons = 0;
    for (int i(0); i < n; ++i) {
      for (int j(i+1); j < n; ++j) {
        int g = gcd(numbers[i], numbers[j]);
        ++pairs;
        if (g > 1) ++commons;
      }
    }

    if (commons < pairs)
      cout << fixed << setw(6) << sqrt(6.0*pairs/(pairs-commons)) << endl;
    else
      cout << "No estimate for this data set." << endl;
  }

  return 0;
}
