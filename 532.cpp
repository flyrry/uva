#include <iostream>
#include <queue>

using namespace std;

int maze[30][30][30];

struct coord {
  int x, y, z;
};

coord dirs[6] = {{1,0,0}, {-1,0,0}, {0,1,0}, {0,-1,0}, {0,0,1}, {0,0,-1}};

int main(void) {
  int L, R, C;
  while (cin >> L >> R >> C) {
    if (!L) break;
    queue<coord> q;
    coord s, e;
    memset(maze, 0, sizeof maze);
    string row;
    for (int z = 0; z < L; ++z) {
      for (int y = 0; y < R; ++y) {
        cin >> row;
        for (int x = 0; x < C; ++x) {
          switch (row[x]) {
            case '.':
              maze[x][y][z] = 0;
              break;
            case 'S':
              s.x = x; s.y = y; s.z = z;
              maze[x][y][z] = 1;
              break;
            case 'E':
              e.x = x; e.y = y; e.z = z;
            default:
              maze[x][y][z] = -1;
              break;
          }
        }
      }
    }

    --L; --R; --C;

    q.push(s);
    int nx, ny, nz;
    bool escaped = false;
    while (!q.empty()) {
      coord c = q.front();
      q.pop();

      for (int i = 0; i < 6; ++i) {
        nx = c.x + dirs[i].x;
        ny = c.y + dirs[i].y;
        nz = c.z + dirs[i].z;
        if (nx > C || nx < 0 ||
            ny > R || ny < 0 ||
            nz > L || nz < 0 ) continue;
        if (e.x == nx && e.y == ny && e.z == nz) {
          cout << "Escaped in " << maze[c.x][c.y][c.z] << " minute(s)." << endl;
          escaped = true;
          while (!q.empty()) q.pop();
          break;
        }
        if (maze[nx][ny][nz] == 0) {
          maze[nx][ny][nz] = maze[c.x][c.y][c.z] + 1;
          coord cd;
          cd.x = nx;
          cd.y = ny;
          cd.z = nz;
          q.push(cd);
        }
      }
    }
    if (!escaped) cout << "Trapped!" << endl;
  }
  return 0;
}
