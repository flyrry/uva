#include <iostream>

using namespace std;

typedef long long llong;

#define N 30000*500+1;

llong str[500][2];

int main(void) {
  int n, r, s;
  cin >> n;
  while (n--) {
    memset(str, 0, sizeof str);
    cin >> r;
    for(int i = 0; i < r; ++i) {
      cin >> s;
      str[i][0] = s;
    }
    for (int i = 0; i < r; ++i) {
      for(int j = 0; j < r; ++j) {
        str[i][1] += abs(str[i][0] - str[j][0]);
      }
    }
    // find minimal;
    llong dist = N;
    for (int i = 0; i < r; ++i) {
      if (str[i][1] < dist) dist = str[i][1];
    }
    cout << dist << endl;
  }
  return 0;
}
