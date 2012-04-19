#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  double cube;
  double perfect[101];
  for (int i(0); i < 101; ++i)
    perfect[i] = i * i * i;
  while (cin >> cube) {
    if (!cube) break;

    int root_idx = upper_bound(perfect, perfect + 101, cube) - perfect - 1;
    double closest_cube = perfect[root_idx];
    //cout << root_idx << " => " << closest_cube << endl;
    cout << fixed << setprecision(4) << (root_idx + (cube - closest_cube)/3/(double)root_idx/(double)root_idx) << endl;
  }
  return 0;
}
