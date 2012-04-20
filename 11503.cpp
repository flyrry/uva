#include <iostream>
#include <map>

#define MAX_FRIENDS 100000

using namespace std;

int parent[MAX_FRIENDS];
int rank[MAX_FRIENDS];
int sizes[MAX_FRIENDS];

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

int main()
{
  ios::sync_with_stdio(false);
  size_t cases;
  cin >> cases;
  while (cases--) {
    map<string, int> ids;
    int friendships;
    register int next_id = 0;
    cin >> friendships;
    for (int i(0); i < friendships; ++i) {
      string person;
      int id1, id2;
      
      cin >> person;
      if (!ids.count(person)) {
        ids[person] = next_id;
        parent[next_id] = next_id;
        rank[next_id] = 0;
        sizes[next_id] = 1;
        ++next_id;
      }
      id1 = ids[person];

      cin >> person;
      if (!ids.count(person)) {
        ids[person] = next_id;
        parent[next_id] = next_id;
        rank[next_id] = 0;
        sizes[next_id] = 1;
        ++next_id;
      }
      id2 = ids[person];

      int size1 = sizes[find_root(id1)];
      int size2 = sizes[find_root(id2)];
      if (join_sets(id1, id2))
        sizes[find_root(id1)] = size1 + size2;
      cout << sizes[find_root(id1)] << endl;
    }
  }
  return 0;
}
