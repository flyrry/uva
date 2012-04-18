#include <iostream>
#include <set>
#include <queue>

using namespace std;

#define N(a) (a - 'A')

typedef set<char> areas;

int main(void)
{
  ios::sync_with_stdio(false);
  int asleep, connections;
  char a, b;
  while (cin >> asleep >> connections) {
    areas brain[26];
    int awake[26];
    queue<pair<char, int> > next;
    size_t awaken = 0;

    for (int i(0); i < 26; ++i)
      awake[i] = 0;

    for (int i(0); i < 3; ++i) {
      cin >> a;
      awake[N(a)] = 3;
      next.push(make_pair(N(a), 0));
    }
    

    for (int i(0); i < connections; ++i) {
      cin >> a >> b;
      brain[N(a)].insert(N(b));
      brain[N(b)].insert(N(a));
    }

    int depth = 0;
    for (; !next.empty(); next.pop()) {
      char n = next.front().first;
      depth = next.front().second;
      ++awaken;
      for (areas::const_iterator a(brain[n].begin()), end(brain[n].end()); a != end; ++a) {
        if (++awake[*a] == 3)
          next.push(make_pair(*a, depth + 1));
      }
    }

    if (awaken == asleep)
      cout << "WAKE UP IN, " << depth << ", YEARS" << endl;
    else
      cout << "THIS BRAIN NEVER WAKES UP" << endl;
  }

  return 0;
}
