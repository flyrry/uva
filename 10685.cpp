#include <iostream>
#include <map>
#include <algorithm>

#define MAX_CREATURES 5000

using namespace std;

// disjoint sets begin
int parent[MAX_CREATURES];
int rank[MAX_CREATURES];

int find_root(int x) {
  if (parent[x] != x)
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

inline bool compare_chains_by_size(const pair<int, int>& lhs, const pair<int, int>& rhs) {
  return lhs.second < rhs.second;
}

int main()
{
  ios::sync_with_stdio(false);
  int creatures, relations;
  map<string, int> id;
  while (cin >> creatures >> relations) {
    if (!creatures && !relations) break;

    for (int i(0); i < creatures; ++i) {
      string name;
      cin >> name;
      parent[i] = i;
      id[name] = i;
    }

    for (int i(0); i < relations; ++i) {
      string food, predator;
      cin >> food >> predator;
      join_sets(id[predator], id[food]);
    }

    map<int, int> chains;
    for (int i(0); i < creatures; ++i) {
      ++chains[find_root(i)];
    }

    cout << max_element(chains.begin(), chains.end(), compare_chains_by_size)->second << endl;
  }
  return 0;
}
