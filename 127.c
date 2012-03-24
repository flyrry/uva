#include <stdio.h>
#include <unistd.h>

typedef struct {
  int buf[52][2];
  int p;
} stack;

void push(stack* s, int c, int v) {
  ++s->p;
  s->buf[s->p][0] = c;
  s->buf[s->p][1] = v;
}

void reset(stack* s) {
  s->p = -1;
}

int topv(stack* s) {
  return s->buf[s->p][0];
}

int tops(stack* s) {
  return s->buf[s->p][1];
}

void pop(stack* s) {
  --s->p;
}

int size(stack* s) {
  return s->p + 1;
}

typedef struct __pile {
  stack cards;
  struct __pile* prev;
  struct __pile* next;
} pile;

pile deck[52];
char c, v;
const char* str_p1 = "pile";
const char* str_p2 = "piles";
const char* str_r = "remaining:";

#define BUFF_SIZE 1024*1024*3
#define INPUT 26 * 3 * 2

int main(void) {
  char in[BUFF_SIZE], out[BUFF_SIZE];
  register ssize_t wsz = 0, rsz, trsz; /* written bytes, read bytes and total processed bytes */
  for (;;) {
    trsz = 0;
    while ((INPUT - trsz) && (rsz = read(0, in + trsz, INPUT - trsz)) > 0) trsz += rsz;
    /*printf("%ld chars read\n", rsz);*/
    register char* f = in;
    register pile* prev = 0;
    register pile* p;
    register pile* last;
    p = deck;
    for (p = deck;; ++p) {
      /*
      c = fgetc(stdin);
      v = fgetc(stdin);
      */
      c = *f++;
      if (c == '#') goto end;
      v = *f++;
      /*
      fgetc(stdin);
      */
      f++;
      reset(&p->cards);
      push(&p->cards, c, v);
      p->prev = prev;
      if (prev) prev->next = p;
      prev = p;
      if (p == &deck[51]) break;
    }
    p->next = 0;
    p = deck;
    last = 0;
    while (p) {
      pile* m = 0;
      pile* p3 = p;
      if ((p3 = p->prev) && (p3 = p3->prev) && (p3 = p3->prev)) {
        if (topv(&p3->cards) == topv(&p->cards) || tops(&p3->cards) == tops(&p->cards)) {
          m = p3;
        }
      }
      pile* p1 = 0;
      if (!m && (p1 = p->prev)) {
        if (topv(&p1->cards) == topv(&p->cards) || tops(&p1->cards) == tops(&p->cards)) {
          m = p1;
        }
      }
      if (m) {
        push(&m->cards, topv(&p->cards), tops(&p->cards));
        pop(&p->cards);
        if (!size(&p->cards)) {
          p->prev->next = p->next;
          if (p->next) p->next->prev = p->prev;
        }
        p = m;
      } else {
        last = p;
        p = p->next;
      }
    }
    int sz = 1;
    p = last;
    while (p->prev) {
      ++sz;
      p = p->prev;
    }

    if (sz > 9)
      out[wsz++] = sz / 10 + '0';
    out[wsz++] = sz % 10 + '0';
    out[wsz++] = ' ';
    register const char* of;
    if (sz == 1)
      of = str_p1;
    else
      of = str_p2;
    while (*of) out[wsz++] = *of++;
    out[wsz++] = ' ';
    of = str_r;
    while (*of) out[wsz++] = *of++;

    /*
     * above is equal to this
    printf("%d %s %s", sz, (sz == 1) ? str_p1 : str_p2, str_r);
    */

    while (p) {
      sz = size(&p->cards);
      out[wsz++] = ' ';
      if (sz > 9)
        out[wsz++] = sz / 10 + '0';
      out[wsz++] = sz % 10 + '0';
      p = p->next;
    }
    out[wsz++] = '\n';
    /*
     * above is equal to this
    while (p) {
      printf(" %d", size(&p->cards));
      p = p->next;
    }
    printf("\n");
    */
  }
end:
  trsz = 0;
  while ((trsz = write(1, out, wsz - trsz)) > 0);
  return 0;
}
