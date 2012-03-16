#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  long double n, A;
  size_t cases = 0;
  while (cin >> n) {
    if (n < 3)
      break;
    cin >> A;

    long double a = sqrt(A/n/tan(acos(-1)/n));
    long double r = sqrt((2*A)/n/sin(2*acos(-1)/n));

    long double spectatorsA = (acos(-1)*r*r) - A;
    long double officialsA = A - (acos(-1)*a*a);

    cout << "Case " << ++cases << ": " << fixed << setprecision(5) << spectatorsA << " " << officialsA << endl;
  }
  return 0;
}
