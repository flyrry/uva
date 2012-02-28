#include <iostream>

using namespace std;

int main(void)
{
  ios::sync_with_stdio(false);
  size_t n;
  while (cin >> n) {
    if (!n) break;
    if (n > 101)
      cout << "f91(" << n << ") = " << n-10 << endl;
    else
      cout << "f91(" << n << ") = 91" << endl;
  }
  return 0;
}
