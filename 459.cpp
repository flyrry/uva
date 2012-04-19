#include <iostream>
#include <string>

using namespace std;

#define N(a) (a - 'A')

// disjoint sets begin

int parent[26];
int rank[26];

void make_set(int x) {
  if (parent[x] == -1) {
    parent[x] = x;
    rank[x] = 0;
  }
}

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

int trees[26];

int main()
{
  ios::sync_with_stdio(false);
  size_t cases;
  string line;
  bool first = true;
  cin >> cases;
  while (cases--) {
    do { getline(cin, line); } while(line.empty());
    int max_node = N(line[0]);
    //cout << "max node is " << (char)line[0] << " or " << max_node << endl;
    for (int i(0); i <= max_node; ++i) {
      parent[i] = -1;
      trees[i] = 0;
      make_set(i);
    }
    //make_set(max_node);

    for (;;) {
      if (!getline(cin, line) || line.empty()) {
        for (int i(0); i <= max_node; ++i)
          trees[find_root(i)] = 1;
        size_t unique_trees = 0;
        for (int i(0); i <= max_node; ++i)
          if (trees[i]) ++unique_trees;
        if (!first) cout << endl;
        first = false;
        cout << unique_trees << endl;
        break;
      }
      int a = N(line[0]);
      int b = N(line[1]);
      //cout << "combining " << a << " and " << b << endl;
      make_set(a);
      make_set(b);
      join_sets(a, b);
    }

  }
  return 0;
}
