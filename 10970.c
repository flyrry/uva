#include <unistd.h>
#include <math.h>

#define BUFF_SZ 1048576

int main(void)
{
  char in[BUFF_SZ], out[BUFF_SZ];
  register ssize_t rsz;
  char* f;

  while ((rsz = read(0, in, BUFF_SZ)) > 0) {
    f = in;
    register ssize_t wsz = 0, bsz = 0;
    for (;f-in<rsz-2;) {
      register int m = strtol(f, &f, 10);
      register int n = strtol(f, &f, 10);
      register int result = m * n - 1;

      if (!result) {
        out[bsz++] = '0';
        out[bsz++] = '\n';
      } else {
        register int digits = log10(result);
        while (result > 0) {
          out[bsz++ + digits--] = (result % 10) + '0';
          result /= 10;
          --digits;
        }
        out[bsz++] = '\n';
      }
    }
    while ((wsz = write(1, out, bsz-wsz)));
  }
  return 0;
}
