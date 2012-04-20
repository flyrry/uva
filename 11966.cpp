#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

#define MAX_STARS 1000

typedef pair<double, double> coord;
typedef vector<coord> coords;

// disjoint sets

int parent[MAX_STARS];
int rank[MAX_STARS];

int find_root(int x) {
  if (x != parent[x])
    parent[x] = find_root(parent[x]);
  return parent[x];
}

void join_sets(int x, int y) {
  int x_root = find_root(x);
  int y_root = find_root(y);
  if (x_root == y_root) return;
  if (rank[x_root] > rank[y_root])
    parent[y_root] = x_root;
  else if (rank[y_root] > rank[x_root])
    parent[x_root] = y_root;
  else {
    parent[x_root] = y_root;
    ++rank[y_root];
  }
}

inline double distance(double x1, double y1, double x2, double y2) {
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int main()
{
  ios::sync_with_stdio(false);
  size_t tests;
  cin >> tests;
  for (int t(1); t <= tests; ++t) {
    int nstars;
    double max_distance;
    cin >> nstars >> max_distance;
    vector<coord> stars;
    stars.reserve(nstars);
    for (int i(0); i < nstars; ++i) {
      parent[i] = i;
      rank[i] = 0;
      double x, y;
      cin >> x >> y;
      int j = 0;
      for (coords::iterator s(stars.begin()), end(stars.end()); s != end; ++s, ++j) {
        if (distance(x, y, s->first, s->second) <= max_distance)
          join_sets(i, j);
      }
      stars.push_back(make_pair(x, y));
    }

    set<int> constellations;
    for (int i(0); i < nstars; ++i)
      constellations.insert(find_root(i));

    cout << "Case " << t << ": " << constellations.size() << endl;
  }
  return 0;
}
