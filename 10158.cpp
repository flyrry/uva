#include <iostream>
#include <cstring>

using namespace std;

#define MAX_PEOPLE 10000

// disjoint sets begin
int parent[2 * MAX_PEOPLE + 2];
int rank[2 * MAX_PEOPLE + 2];

inline void make_set(int x) {
  parent[MAX_PEOPLE + x] = x;
  rank[MAX_PEOPLE + x] = 0;
}

int find_root(int x) {
  if (parent[MAX_PEOPLE + x] != x)
    parent[MAX_PEOPLE + x] = find_root(parent[MAX_PEOPLE + x]);
  return parent[MAX_PEOPLE + x];
}

bool join_sets(int x, int y) {
  int x_root = find_root(x);
  int y_root = find_root(y);
  if (x_root == y_root)
    return false; // already in the same set
  if (rank[MAX_PEOPLE + x_root] > rank[MAX_PEOPLE + y_root]) {
    parent[MAX_PEOPLE + y_root] = x_root;
  } else if (rank[MAX_PEOPLE + x_root] < rank[MAX_PEOPLE + y_root]) {
    parent[MAX_PEOPLE + x_root] = y_root;
  } else {
    parent[MAX_PEOPLE + x_root] = y_root;
    ++rank[MAX_PEOPLE + y_root];
  }
  return true;
}

inline bool same_set(int x, int y) {
  return find_root(x) == find_root(y);
}

inline bool in_a_set(int x) {
  return parent[MAX_PEOPLE + x];
}
// disjoint sets end

inline bool are_friends(int x, int y) {
  return (same_set(x, y) || same_set(-x, -y));
}

inline bool are_enemies(int x, int y) {
  return (same_set(x, -y) || same_set(-x, y));
}

int main()
{
  ios::sync_with_stdio(false);
  register int op, x, y;
  int n;
  cin >> n;
  memset(parent, 0, sizeof(int) * (MAX_PEOPLE * 2 + 2));

  while (cin >> op >> x >> y) {
    if (!op) break;

    // friends are in [1..n], enemies in [-1..-n]
    x = x + 1;
    y = y + 1;

    if (!(in_a_set(x))) make_set(x);
    if (!(in_a_set(y))) make_set(y);
    if (!(in_a_set(-x))) make_set(-x);
    if (!(in_a_set(-y))) make_set(-y);

    switch (op) {
      case 1:
        if (are_enemies(x, y))
          cout << "-1" << endl;
        else {
          join_sets(x, y);
          join_sets(-x, -y); // join enemies
        }
        break;
      case 2:
        if (are_friends(x, y))
          cout << "-1" << endl;
        else {
          join_sets(x, -y); // enemy of an enemy is a friend
          join_sets(y, -x);
        }
        break;
      case 3:
        cout << (are_friends(x, y) ? "1" : "0") << endl;
        break;
      case 4:
        cout << (are_enemies(x, y) ? "1" : "0") << endl;
    }
  }

  return 0;
}
