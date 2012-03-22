#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);

  int skyline[10000];
  memset(skyline, -1, sizeof(int) * 10000);
  int l, h, r, max_r;
  while (cin >> l >> h >> r) {
    max_r = max(r, max_r);
    replace_if(skyline+l, skyline+r, bind2nd(less<int>(), h), h);
  }

  int prev = -1;

  for (int i = 0; i < max_r; ++i) {
    if (prev == skyline[i])
      continue;
    cout << i << " " << max(skyline[i], 0) << " ";
    prev = skyline[i];
  }
  cout << max_r << " " << 0 << endl;

  return 0;
}
