#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  size_t cases;
  cin >> cases;
  while (cases--) {
    int sum, diff;
    cin >> sum >> diff;
    if (sum < diff || (sum % 2 && !(diff % 2)) || (!(sum % 2) && diff % 2))
      cout << "impossible" << endl;
    else {
      int a = (sum - diff) / 2;
      int b = abs(sum - a);
      cout << max(a, b) << " " << min(a, b) << endl;
    }
  }
  return 0;
}
