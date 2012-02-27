#include <iostream>
using namespace std;

int main(void)
{
  ios::sync_with_stdio(false);
  size_t T, cases = 0;
  cin >> T;
  while (T--) {
    int a,b;
    cin >> a >> b;
    a = a % 2 ? a : a + 1;
    b = b % 2 ? b : b - 1;

    /* not testing for a>0,b=0, since a <= b is given*/
    cout << "Case " << ++cases << ": " << ((b-a)/2 + 1)*(a+b)/2 << endl;
  }
  return 0;
}
