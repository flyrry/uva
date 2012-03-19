#include <cstdio>
#include <queue>

using namespace std;

char map[21][21];
int dir[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
char land;
int m, n;

typedef pair<int, int> region;

size_t fill(int x, int y)
{
  queue<region> regions;
  size_t area = 0;
  for (regions.push(make_pair(x, y)); !regions.empty(); regions.pop()) {
    region r = regions.front();
    if (map[r.first][r.second] != land)
      continue;
    map[r.first][r.second] = land + 1;
    ++area;
    for (int i = 0; i < 4; ++i) {
      int nx = r.first + dir[i][0];
      if (nx < 0 || nx >= m)
        continue;
      int ny = (r.second + dir[i][1] + n) % n;
      regions.push(make_pair(nx, ny));
    }
  }
  return area;
}

int main()
{
  int x, y;
  while (scanf("%d %d", &m, &n) != EOF) {
    size_t max_area = 0;
    for (int i = 0; i < m; ++i) {
      scanf("%s", map[i]);
    }
    scanf("%d %d", &x, &y);
    land = map[x][y];
    fill(x, y);

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (map[i][j] != land)
          continue;
        size_t area = fill(i, j);
        max_area = (area > max_area) ? area : max_area;
      }
    }

    printf("%d\n", max_area);
  }
  return 0;
}
