#include <unistd.h>
#include <math.h>

#define BUFF_SZ 1048576*2

int main(void)
{
  char in[BUFF_SZ], out[BUFF_SZ];
  register ssize_t rsz; /* read bytes */

  while ((rsz = read(0, in, BUFF_SZ)) > 0) {
    register char* f = in;
    register ssize_t wsz = 0, bsz = 0; /* written bytes and buffer size */
    for (; f - in < rsz - 1;) {
      register int m = 0;
      while (*f < '0' || *f > '9') ++f; /* skip garbage */
      for (; *f >= '0' && *f <= '9'; ++f) { /* compose number from digits */
        m *= 10;
        m += (*f - '0');
      }
      register int n = 0;
      while (*f < '0' || *f > '9') ++f; /* skip garbage */
      for (; *f >= '0' && *f <= '9'; ++f) { /* compose number from digits */
        n *= 10;
        n += (*f - '0');
      }
      register int result = m * n - 1;

      /* convert result into string and write into buf */
      /* special case for 0 due to log10(0) */
      /* numbers are written backwards, meanwhile buffer size keeps growing */
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
