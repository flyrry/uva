#include <iostream>

using namespace std;

int main(void)
{
  ios::sync_with_stdio(false);
  int n,m,x,y,k;
  while (cin >> k) {
    if (!k) return 0;
    cin >> n >> m;
    while (k--) {
      cin >> x >> y;
      if (x == n || y == m)
        cout << "divisa\n";
      else if (x < n && y > m)
        cout << "NO\n";
      else if (x > n && y > m)
        cout << "NE\n";
      else if (x > n && y < m)
        cout << "SE\n";
      else
        cout << "SO\n";
    }
  }
  return 0;
}
