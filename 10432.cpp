#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  double r, n;
  const double pi = atan(1) * 4;
  while (cin >> r >> n) {
    cout << fixed << setprecision(3) << r * sin(pi / n) * r * cos(pi / n) * n << endl;
  }
  return 0;
}
