#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

#define MAX_PEOPLE 30001

// disjoint sets begin

int parent[MAX_PEOPLE];
int rank[MAX_PEOPLE];

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

// disjoint sets end

int main()
{
  ios::sync_with_stdio(false);
  size_t cases;
  cin >> cases;
  while (cases--) {
    int citizens, pairs;
    cin >> citizens >> pairs;
    for (int i(1); i <= citizens; ++i) {
      parent[i] = i;
    }
    for (int i(0); i < pairs; ++i) {
      int a, b;
      cin >> a >> b;
      join_sets(a, b);
    }

    map<int, int> friends;
    for (int i(1); i <= citizens; ++i)
      ++friends[find_root(i)];
    int max_circle = 0;
    for (map<int, int>::const_iterator f(friends.begin()), end(friends.end()); f != end; ++f)
      max_circle = max(f->second, max_circle);
    cout << max_circle << endl;
  }
  return 0;
}
