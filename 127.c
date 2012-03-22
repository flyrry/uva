#include <stdio.h>

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

int main(void) {
  for (;;) {
    register pile* prev = 0;
    register pile* p;
    register pile* last;
    p = deck;
    for (p = deck;; ++p) {
      c = fgetc(stdin);
      v = fgetc(stdin);
      if (c == '#') return 0;
      fgetc(stdin);
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
    printf("%d %s %s", sz, (sz == 1) ? str_p1 : str_p2, str_r);
    while (p) {
      printf(" %d", size(&p->cards));
      p = p->next;
    }
    printf("\n");
  }
}
