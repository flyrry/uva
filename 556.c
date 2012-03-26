#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CAN_MOVE_TO(x, y) ((x) < w && (y) < b && (x) >= 0 && (y) >= 0 && maze[(y)][(x)] != '1')

enum { X = 0, Y };

short left[][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
short right[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int main()
{
  int b, w, i, k;
  while (scanf("%d %d\n", &b, &w) != EOF) {
    if (!b && !w) return 0;
    char** maze = (char**)malloc(b * sizeof(char*));
    for (i = 0; i < b; ++i)
      maze[i] = (char*)malloc(w * sizeof(char));
    size_t* visits = (size_t*)calloc(b * w, sizeof(size_t));

    for (i = 0; i < b; ++i)
      scanf("%s\n", maze[i]);

    size_t walls = 0;
    for (i = 0; i < b; ++i) {
      for (k = 0; k < w; ++k) {
        if (maze[i][k] == '1')  ++walls;
      }
    }
    /*
    for (i = 0; i < b; ++i) {
      for (k = 0; k < w; ++k)
        printf("%c", maze[i][k]);
      printf("\n");
    }
    */

    int y = b - 1;
    int x = 0;
    int dir = 0;
    for (;;) {
      int next_x = x + right[dir][X];
      int next_y = y + right[dir][Y];

      if (!CAN_MOVE_TO(next_x, next_y)) {
        next_x = x + left[dir][X];
        next_y = y + left[dir][Y];
      } else {
        dir = (dir + 3) % 4;
      }

      if (CAN_MOVE_TO(next_x, next_y)) {
        ++visits[y * w + x];
        x = next_x;
        y = next_y;
        if ((next_y == b-1) && (next_x == 0)) break;
      } else {
        dir = (dir + 1) % 4;
      }
    }

    size_t times[5] = {0, 0, 0, 0, 0};
    size_t t;
    for (i = 0; i < b; ++i)
    {
      for (k = 0; k < w; ++k) {
        t = visits[i * w + k];
        if (t < 5)
          ++times[t];
      }
    }

    printf("%3d%3d%3d%3d%3d\n", (times[0] < walls) ? 0 : times[0] - walls, times[1], times[2], times[3], times[4]);

    for (i = 0; i < b; ++i)
      free(maze[i]);
    free(maze);
  }
  return 0;
}
