#include <iostream>
#include <cstring>

using namespace std;

enum {
  BIT = 0,
  X,
  Y,
  FIELD_DEPTH
};

#define FIELD_SIZE 101

int main()
{
  ios::sync_with_stdio(false);
  size_t n;
  char field[FIELD_SIZE][FIELD_SIZE][FIELD_DEPTH];
  memset(field, 0, sizeof(char) * FIELD_SIZE * FIELD_SIZE * (size_t)FIELD_DEPTH);
  while (cin >> n) {
    if (!n) break;
    for (int y = 1; y <= n; ++y) {
      for (int x = 1; x <= n; ++x) {
        cin >> field[y][x][BIT];
        field[y][x][X] = field[y][x][BIT] + field[y][x-1][X];
        field[y][x][Y] = field[y][x][BIT] + field[y-1][x][Y];
      }
    }

    int odd_x = 0, odd_y = 0, oddities = 0;
    for (int x = 1, y = n; x <= n; ++x) {
      if (field[n][x][Y] % 2) {
        odd_x = x;
        oddities++;
      }
    }
    for (int y = 1, x = n; y <= n; ++y) {
      if (field[y][n][X] % 2) {
        odd_y = y;
        oddities++;
      }
    }
    if (!oddities)
      cout << "OK" << endl;
    else if (oddities == 2 && !!odd_x && !!odd_y)
      cout << "Change bit (" << odd_y << "," << odd_x << ")" << endl;
    else
      cout << "Corrupt" << endl;
  }
  return 0;
}
