#include <iostream>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  size_t a,b;
  while (cin >> a >> b)
    cout << (a^b) << endl;
  return 0;
}
