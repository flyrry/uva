#include <cstdio>
#include <queue>

using namespace std;

char grid[101][101];
int m, n;
int dir[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
const char OIL = '@';
typedef pair<int, int> plot;

void fill(int x, int y)
{
  queue<plot> plots;
  for (plots.push(make_pair(x, y)); !plots.empty(); plots.pop()) {
    plot p = plots.front();
    if (grid[p.first][p.second] != OIL)
      continue;
    ++grid[p.first][p.second];
    for (int i(0); i < 8; ++i) {
      int nx = p.first + dir[i][0];
      if (nx < 0 || nx >= m)
        continue;
      int ny = p.second + dir[i][1];
      if (ny < 0 || ny >= n)
        continue;
      plots.push(make_pair(nx, ny));
    }
  }
}

int main()
{
  while (scanf("%d %d", &m, &n) != EOF) {
    if (!m)
      break;
    for (int i(0); i < m; ++i)
      scanf("%s", grid[i]);
    size_t deposits(0);
    for (int i(0); i < m; ++i) {
      for (int j(0); j < n; ++j) {
        if (grid[i][j] != OIL)
          continue;
        fill(i, j);
        ++deposits;
      }
    }
    printf("%d\n", deposits);
  }
  return 0;
}
