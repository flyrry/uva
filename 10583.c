#include <stdio.h>

#define MAX_STUDENTS 50001

/* 
 * disjoint sets begin
 */
int parent[MAX_STUDENTS];
int rank[MAX_STUDENTS];

/* ensures that x is a set */
void ensure_set(int x) {
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

int join_sets(int x, int y) {
  int x_root = find_root(x);
  int y_root = find_root(y);
  if (x_root == y_root)
    return 0; /* same set already */
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

int same_set(int x, int y) {
  return find_root(x) == find_root(y);
}

int polled[MAX_STUDENTS];
int religious[MAX_STUDENTS];

int main(void)
{
  int n, m, c = 0;
  while (scanf("%d %d", &n, &m) != EOF) {
    ++c;
    if (!n) break;
    register int p;
    int i, j;
    for (p = 1; p <= n; ++p) {
      parent[p] = -1;
      polled[p] = 0;
      religious[p] = 0;
    }

    int unasked = n;
    for (p = 0; p < m; ++p) {
      scanf("%d %d", &i, &j);
      ensure_set(i);
      ensure_set(j);
      join_sets(i, j);

      if (!polled[i]) {
        polled[i] = 1;
        --unasked;
      }
      if (!polled[j]) {
        polled[j] = 1;
        --unasked;
      }
    }
    size_t religions = 0;
    /* update parent node of each set to ensure only unique sets are listed */
    for (p = 1; p <= n; ++p)
      parent[p] = find_root(p);
    /* mark unique sets */
    for (p = 1; p <= n; ++p)
      if (parent[p] != -1)
        religious[parent[p]] = 1;
    /* count unique sets */
    for (p = 1; p <= n; ++p)
      if (religious[p])
        ++religions;
    printf("Case %d: %d\n", c, religions + unasked);
  }
  return 0;
}
