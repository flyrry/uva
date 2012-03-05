#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 133
int repeat = 0;
char out[MAX_LINE_LENGTH];
int j = 0;

void print_maze_line(char c) {
  int i;
  for (i = 0; i < (repeat ? repeat : 1); ++i) {
    if (j > MAX_LINE_LENGTH-1) {
      printf("%s", out);
      memset(out, 0, sizeof(char) * MAX_LINE_LENGTH);
      j = 0;
    }
    out[j++] = c;
  }
  repeat = 0;
}

int main()
{
  char symbol;
  memset(out, 0, sizeof(char) * MAX_LINE_LENGTH);
  while ((symbol = getchar()) != EOF) {
    if (symbol >= '0' && symbol <= '9') {
      repeat += symbol - '0';
    } else if (symbol == 'b') {
      print_maze_line(' ');
    } else if (symbol == '!' || symbol == '\n') {
      print_maze_line('\n');
    } else {
      print_maze_line(symbol);
    }
  }
  printf("%s", out);
  return 0;
}
