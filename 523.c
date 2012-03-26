#include <stdio.h>
#include <limits.h>
#include <string.h>

#define VERTICES 1000
#define DEGREE 1000

int edges[VERTICES][DEGREE];
int weights[VERTICES][VERTICES];
int taxes[VERTICES];
unsigned char visited[VERTICES];
int distance[VERTICES];
int parent[VERTICES];
int degree[VERTICES];
int way[VERTICES];

int endline;
int cities;
int cases;
int from,to;
int num;
int i, j;
int found;
char *p;
char path[256];

int current;
int target;
int weight;
int k;
int dist;

void add_edge(int from, int to, int weight) {
  /*printf("adding path from %d to %d with %d\n", from, to, weight);*/
  edges[from][degree[from]] = to;
  degree[from]++;
  weights[from][to] = weight;
}

void dijkstra(int from, int to) {
  if (from == to) {
    printf("From %d to %d :\nPath: %d\nTotal cost : 0\n", from, from, from);
    return;
  }

  memset(visited, 0, sizeof visited);
  for (k = 1; k <= cities; ++k) {
    distance[k] = INT_MAX;
    parent[k] = -1;
  }

  distance[from] = 0;
  current = from;

  while (!visited[current]) {
    visited[current] = 1;

    if (current == to) {
      /* Answer is found. */
      way[0] = target = to;
      k = 1;
      while ((target = parent[target]) != from)
        way[k++] = target;
      way[k] = from;

      printf("From %d to %d :\nPath: ", from, to);
      current = 0; /* current is simply a flag here */
      while (k >= 0) {
        if (current++ > 0) printf("-->");
        printf("%d", way[k--]);
      }

      printf("\nTotal cost : %d\n", distance[to]);
      return;
    }

    for (k = 0; k < degree[current]; ++k) {
      target = edges[current][k];
      weight = weights[current][target];
      if (target != to) weight += taxes[target];

      /*printf("DEBUG: node == %d and dest == %d and degree == %d and weight == %d\n", current, target, degree[current], weight);*/

      if (distance[target] > distance[current] + weight) {
        distance[target] = distance[current] + weight;
        parent[target] = current;
      }
    }

    current = from;
    dist = INT_MAX;
    for (k = 1; k <= cities; ++k) {
      if (!visited[k] && dist > distance[k]) {
        dist = distance[k];
        current = k;
      }
    }
  }
}

int main (void) {
  scanf("%d", &cases);
  getchar();

  while (cases--) {
    memset(degree, 0, sizeof degree);
    cities = 0;
    /* determine input size & read first line */
    for (;;) {
      scanf("%d", &num);
      ++cities;
      if (cities == 1 || num == -1)
        if (getchar() == '\n') break;
        else continue;
      add_edge(1, cities, num);
      if (getchar() == '\n') break;
    }
    /* read city distances */
    for (i = 2; i <= cities; ++i) {
      for (j = 1; j <= cities; ++j) {
        scanf("%d", &num);
        if (j == i || num == -1) continue;
        add_edge(i, j, num);
      }
    }
    /* read taxes */
    for (i = 1; i <= cities; ++i) {
      scanf("%d", &num);
      taxes[i] = num;
    }
    getchar();

    for (;;) {
      /* read paths */
      found = 0;
      if (fgets(path, 256, stdin) == NULL) return 0;
      p = path;
      while (*p != '\n') {
        if (*p != ' ' || *p != '\t') {
          found = 1;
          break;
        }
        ++p;
      }
      if (found) {
        sscanf(path, "%d %d", &from, &to);

        if (endline) printf("\n");
        dijkstra(from, to);
        ++endline;
      } else {
        break;
      }
    }
  }

  return 0;
}
