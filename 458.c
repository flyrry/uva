#include <unistd.h>

#define IO_BUFFER_SIZE 1048576

int main(void) {
  register int sz, i;
  char in[IO_BUFFER_SIZE], out[IO_BUFFER_SIZE];
  while ((sz = read(0, in, IO_BUFFER_SIZE)) > 0) {
    for (i = 0; i < sz; ++i)
      out[i] = (in[i] == '\n') ? in[i] : in[i] - 7;
    write(1, out, sz);
  }
  return 0;
}
