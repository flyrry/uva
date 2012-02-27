#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
  char c;
  size_t freq[26];
  memset(freq, 0, sizeof(size_t) * 26);
  while ((c = toupper(getchar())) != EOF) {
    if (isalpha(c)) {
      freq[c-'A']++;
    }
  }
  int i, max_i;
  size_t max;
  while(1) {
    max = 0;
    max_i = -1;
    for (i = 0; i < 26; ++i) {
      if (freq[i] > max) {
        max = freq[i];
        max_i = i;
      }
    }
    if (max_i != -1) {
      freq[max_i] = 0;
      printf("%c %d\n", toupper(max_i+'A'), max);
    } else {
      break;
    }
  }
  return 0;
}
