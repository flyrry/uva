#include <iostream>
#include <limits.h>

using namespace std;

#define NHUMBLES 5842
size_t humbles[NHUMBLES];
int next_base[NHUMBLES];

int main()
{
  ios::sync_with_stdio(false);

  int bases[] = {2, 3, 5, 7};
  humbles[0] = 1;
  next_base[0] = 0;
  for (int low(0), hi(1); hi < NHUMBLES;) {
    int min_c, min = INT_MAX;
    for (int c(low); c < hi; ++c) {
      size_t next = humbles[c] * bases[next_base[c]];
      if (next < min) {
        min = next;
        min_c = c;
      } else if (next == min) {
        ++next_base[c];
      }
    }
    humbles[hi++] = humbles[min_c] * bases[next_base[min_c]];
    if (++next_base[min_c] > 3) while (min_c < NHUMBLES && next_base[min_c++] > 3) ++low;
  }

  int n;
  const char* ords[] = {"th", "st", "nd", "rd", "th", "th", "th", "th", "th", "th"};
  while (cin >> n, n) {
    cout << "The " << n;
    if (n % 100 < 20 && n % 100 > 10) cout << "th";
    else cout << ords[n % 10];
    cout << " humble number is " << humbles[n-1] << "." << endl;
  }

  return 0;
}
