#include <iostream>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  size_t n, k;
  while (cin >> n >> k) {
    size_t smokes = n;
    for (; n / k; n = (n / k) + (n % k))
      smokes += n / k;
    cout << smokes << endl;
  }
  return 0;
}
