#include <stdio.h>
#include <string.h>

int main()
{
  char c, i, j; 
  size_t map[256], max[256], max_frequency = 0;
  memset(map, 0, sizeof(size_t) * 256);
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      for (j = 0, i = 'A'; i != 'z'; ++i) {
        if (i > 'Z' && i < 'a') continue;
        if (map[i] > max_frequency) {
          max_frequency = map[i];
          j = 0;
        }
        if (map[i] == max_frequency)
          max[j++] = i;
      }
      for (i = 0; i < j; ++i)
        printf("%c", max[i]);
      printf(" %d\n", max_frequency);
      max_frequency = 0;
      memset(map, 0, sizeof(size_t) * 256);
    }
    ++map[c];
  }
  return 0;
}
