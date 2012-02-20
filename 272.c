#include <stdio.h>
#include <string.h>

#define BUFFSZ  2097152

int main(int argc, char** argv)
{
  char c = 0;
  char in = 0;
  while ((c = getchar()) != EOF) {
    if (c == '"') {
      in = !in;
      if (in) {
        putchar('`');
        putchar('`');
      } else {
        putchar('\'');
        putchar('\'');
      }
    } else {
      putchar(c);
    }
  }
  return 0;
}
/*
int main(int argc, char** argv)
{
  char in = 0;
  char buff[BUFFSZ];
  char input[BUFFSZ];
  char* p = buff;
  int n = 0;
  while ((n = read(0, input, BUFFSZ)) > 0) {
    char* c = input;
    while (c < input+n) {
      if ( (p-buff) > (BUFFSZ-2) ) {
        write(1, buff, p-buff);
        memset(buff, 0, BUFFSZ);
        p = buff;
      }
      if (*c == '"') {
        in = !in;
        if (in) {
          *p++ = '`';
          *p++ = '`';
        } else {
          *p++ = '\'';
          *p++ = '\'';
        }
      } else {
        *p++ = *c;
      }
      ++c;
    }
  }
  write(1, buff, p-buff);
  return 0;
}
*/
