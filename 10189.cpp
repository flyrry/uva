#include <iostream>
#include <string.h>

int main(void)
{
  std::ios::sync_with_stdio(false);
  size_t n,m,f;
  f = 0;
  char c;
  // * is 42
  // . is 46
  // so we're safe with using char since max adjacent mines is 8
  char field[100][100];
  while (++f) {
    std::cin >> n >> m;
    memset(field, 0, sizeof(char) * 10000);
    if (!(n&&m))
      break;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (std::cin.peek() == '\n')
          std::cin.ignore(1, '\n');
        std::cin.get(c);
        if (c == '*') {
          field[i][j] = 9;
          // increment around this slot
          if (i > 0) {
            field[i-1][j]++;
            if (j > 0)
              field[i-1][j-1]++;
            if (j < m-1)
              field[i-1][j+1]++;
          }
          if (i < n-1) {
            field[i+1][j]++;
            if (j > 0)
              field[i+1][j-1]++;
            if (j < m-1)
              field[i+1][j+1]++;
          }
          if (j > 0)
            field[i][j-1]++;
          if (j < m-1)
            field[i][j+1]++;
        }
      }
    }

    if (f > 1)
      std::cout << std::endl;
    std::cout << "Field #" << f << ":" << std::endl;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (field[i][j] > 8)
          std::cout << '*';
        else
          std::cout << (size_t)field[i][j];
      }
      std::cout << std::endl;
    }
  }
  return 0;
}
