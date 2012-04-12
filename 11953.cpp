#include <cstdio>
#include <queue>

using namespace std;

typedef pair<int, int> point;

int dir[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool fill(int x, int y, int n, char grid[][101])
{
  if (grid[x][y] != 'x' && grid[x][y] != '@')
    return false;
  bool alive_ship = false;
  queue<point> points;
  for (points.push(make_pair(x, y)); !points.empty(); points.pop()) {
    point p = points.front();
    if (grid[p.first][p.second] == 'x')
      alive_ship = true;
    else if (grid[p.first][p.second] != '@')
      continue;
    ++grid[p.first][p.second]; // just invalidate the point
    for (int i(0); i < 4; ++i) {
      int nx = p.first + dir[i][0];
      if (nx < 0 || nx >= n) continue;
      int ny = p.second + dir[i][1];
      if (ny < 0 || ny >= n) continue;
      points.push(make_pair(nx, ny));
    }
  }
  return alive_ship;
}

int main()
{
  int cases;
  char grid[101][101];
  scanf("%d", &cases);
  for (int c(1); c <= cases; ++c) {
    int n;
    scanf("%d", &n);
    for (int i(0); i < n; ++i)
      scanf("%s", grid[i]);
    size_t ships(0);
    for (int i(0); i < n; ++i)
      for (int j(0); j < n; ++j)
        if (fill(i, j, n, grid))
          ++ships;
    printf("Case %d: %d\n", c, ships);
  }
  return 0;
}
