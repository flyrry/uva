#include <iostream>
#include <cstring>

using namespace std;

#define RANGE 1000001

bool busy[RANGE];

int main()
{
  ios::sync_with_stdio(false);

  size_t n, m, s, e, p; // n, m, start, end, period

  while ((cin >> n >> m) && (n | m)) {
    memset(busy, false, RANGE);
    bool conflict = false;
    for (size_t i(0); i < n; ++i) {
      cin >> s >> e;
      if (!conflict) {
        for (; !conflict && (s < e); ++s) {
          if (busy[s])
            conflict = true;
          busy[s] = true;
        }
      }
    }
    for (size_t i(0); i < m; ++i) {
      cin >> s >> e >> p;
      if (!conflict) {
        e -= s; // e is now duration
        for (size_t t(0); !conflict && (s + t * p < RANGE); ++t) {
          size_t start = s + t * p;
          size_t end = start + e;
          for (size_t j(start); !conflict && (j < end) && (j < RANGE); ++j) {
            if (busy[j])
              conflict = true;
            busy[j] = true;
          }
        }
      }
    }

    cout << (conflict ? "CONFLICT" : "NO CONFLICT") << endl;
  }

  return 0;
}
