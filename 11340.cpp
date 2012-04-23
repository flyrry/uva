#include <cstdio>
#include <cstring>

#define BUFF_SIZE 128 * 1024

char line[1 << 14];
int values[256];
char out[BUFF_SIZE];

int main()
{
  int cases, lines, v;
  unsigned char c;
  setvbuf(stdout, out, _IOFBF, BUFF_SIZE * sizeof(char));
  scanf("%d\n", &cases);
  while (cases--) {
    scanf("%d\n", &lines);
    int total = 0;
    while (lines--) {
      scanf("%c %d\n", &c, &v);
      values[c] = v;
    }
    scanf("%d\n", &lines);
    while (lines--) {
      fgets(line, 1 << 14, stdin);
      for (v = 0; line[v] != '\n'; ++v)
        total += values[(unsigned char)line[v]];
    }

    printf("%d.%02d$\n", total / 100, total % 100);

    if (cases)
      memset(values, 0, sizeof(values));
  }
  return 0;
}
