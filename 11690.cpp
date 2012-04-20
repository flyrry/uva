#include <iostream>

using namespace std;

#define MAX_FRIENDS 10000

// disjoint sets
int parent[MAX_FRIENDS];
int rank[MAX_FRIENDS];

int find_root(int x) {
  if (x != parent[x])
    parent[x] = find_root(parent[x]);
  return parent[x];
}

int join_sets(int x, int y) {
  int x_root = find_root(x);
  int y_root = find_root(y);
  if (x_root == y_root) return 0;
  if (rank[x_root] > rank[y_root])
    parent[y_root] = x_root;
  else if (rank[y_root] > rank[x_root])
    parent[x_root] = y_root;
  else {
    parent[x_root] = y_root;
    ++rank[y_root];
  }
  return 1;
}

int debt[MAX_FRIENDS];

int main()
{
  ios::sync_with_stdio(false);
  size_t cases;
  cin >> cases;
  while (cases--) {
    int friends, friendships;
    cin >> friends >> friendships;
    for (int i(0); i < friends; ++i) {
      int amount;
      cin >> amount;
      parent[i] = i;
      rank[i] = 0;
      debt[i] = amount;
    }

    for (int i(0); i < friendships; ++i) {
      int a, b; // ids of friends
      cin >> a >> b;
      int debt_a = debt[find_root(a)];
      int debt_b = debt[find_root(b)];
      if (join_sets(a, b))
        debt[find_root(a)] = debt_a + debt_b;
    }

    bool possible = true;
    for (int i(0); i < friends; ++i) {
      if (debt[find_root(i)]) {
        possible = false;
        break;
      }
    }

    cout << (possible ? "POSSIBLE" : "IMPOSSIBLE") << endl;
  }
  return 0;
}
