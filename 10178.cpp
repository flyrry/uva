#include <iostream>

using namespace std;

// disjoint sets

char parent[256];
int rank[256];
int faces;

void make_set(char x) {
  if (parent[x] == -1)
    parent[x] = x;
}

char find_root(char x) {
  if (parent[x] != x)
    parent[x] = find_root(parent[x]);
  return parent[x];
}

void join_sets(char x, char y) {
  char x_root = find_root(x);
  char y_root = find_root(y);
  if (x_root == y_root) {
    ++faces; // looping onto self, add face
    return;
  }
  if (rank[x_root] > rank[y_root])
    parent[y_root] = x_root;
  else if (rank[y_root] > rank[x_root])
    parent[x_root] = y_root;
  else {
    parent[x_root] = y_root;
    ++rank[y_root];
  }
}


int main()
{
  ios::sync_with_stdio(false);
  char a, b;
  int v, e;
  while (cin >> v >> e) {
    faces = 1;
    for (int i(0); i < 256; ++i)
      parent[i] = -1;
    for (int i(0); i < e; ++i) {
      cin >> a >> b;
      make_set(a);
      make_set(b);
      join_sets(a, b);
    }
    cout << faces << endl;
  }
  return 0;
}
