#include <iostream>

using namespace std;

#define MAX_COMPUTERS 100000

int parent[MAX_COMPUTERS];
int rank[MAX_COMPUTERS];

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
  else if (rank[y_root] = rank[x_root])
    parent[x_root] = y_root;
  else {
    parent[x_root] = y_root;
    ++rank[y_root];
  }
}

int main (void) {
  int cases;
  int computers;
  cin >> cases;
  char command;
  int c1, c2;
  int suc_count, unsuc_count;

  while (cases--) {
    suc_count = unsuc_count = 0;
    cin >> computers;

    for (int i = 1; i <= computers; ++i)
      parent[i] = i;

    while (cin >> command >> c1 >> c2) {
      cin.ignore(1000, '\n');

      if (command == 'c') {
        join_sets(c1, c2);
      } else {
        if (find_root(c1) == find_root(c2))
          ++suc_count;
        else
          ++unsuc_count;
      }
      if (cin.peek() == '\n') break;
    }

    cout << suc_count << "," << unsuc_count << endl;
    if (cases) cout << endl;
  }

  return 0;
}
