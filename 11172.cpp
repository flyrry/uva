// what the...
#include <iostream>

using namespace std;

int main(void)
{
  ios::sync_with_stdio(false);
  long long a,b;
  int t;
  cin >> t;
  while (t--) {
    cin >> a >> b;
    if (a < b)
      cout << "<" << endl;
    else if (a > b)
      cout << ">" << endl;
    else
      cout << "=" << endl;
  }
  return 0;
}
