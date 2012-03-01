#include <iostream>
#include <string.h>

using namespace std;
/*
// pretty-print the regions
void pp_regions(int regions[100], size_t n)
{
  for (int i = 0; i < n; ++i) {
    if (regions[i])
      cout << "X ";
    else
      cout << i+1 << " "; // +1 since indexes are shifted due to arrays starting with 0
  }
  cout << endl;
}
*/
int main(void)
{
  ios::sync_with_stdio(false);
  size_t n;
  int regions[100];
  while (cin >> n) {
    if (!n) break;

   for (int m = 1;; ++m) { // m can get bigger than n
      memset(regions, 0, sizeof(int) * 100);
      regions[0] = 1; // marking picked numbers by 1
      //cout << "checking for " << m << endl;
      int picked = 1; // amount of items picked, used to determine if 13 is the last one picked
      int steps = 0; // steps over existing items, to omit all the 0s on the way
      for (int i = 1;;) {
        if (!regions[i]) {
          if (++steps == m) {
            ++picked;
            //cout << "stepping on " << i+1 << " " << picked << " picked so far" << endl;
            //pp_regions(regions, n);
            if (i == 12) break; // since arrays start with 0 this is actually '13'
            regions[i] = 1;
            steps = 0;
          }
        }
        i = (i+1)%n; // mod to loop-over
      }
      if (picked == n) {
        cout << m << endl;
        break;
      }
    }
  }
  return 0;
}
