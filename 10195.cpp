#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  double a, b, c;
  while (cin >> a >> b >> c) {
    double semiperimeter = (a + b + c)/2.0;
    cout << fixed << setprecision(3) << "The radius of the round table is: " << (semiperimeter ? sqrt((semiperimeter - a) * (semiperimeter - b) * (semiperimeter - c) / semiperimeter) : 0.0) << endl;
  }
  return 0;
}
