#include <iostream>

using namespace std;

class Stack {
  int buf[52][2];
  int p;
  public:
  Stack() : p(-1) {}

  void push(int v, int s) {
    ++p;
    buf[p][0] = v;
    buf[p][1] = s;
  }

  void reset() {
    p = -1;
  }

  int topv() {
    return buf[p][0];
  }

  int tops() {
    return buf[p][1];
  }

  void pop() {
    --p;
  }

  int size() {
    return p + 1;
  }
};

struct pile {
  Stack cards;
  pile* prev;
  pile* next;
};

//
// [3H]    [KS][8H]
// [4S]    [AS]
//         [7H]
//

pile deck[52];
string cd;
pile* prev;
/*
void ddeck() {
  for(int i = 0; i < 52; ++i)
    cout << &deck[i] << " " << i << ": " << (char)deck[i].cards.topv() << (char)deck[i].cards.tops() << " " << deck[i].prev << " " << deck[i].next << " " << deck[i].cards.size() << endl;
}
*/
int main(void) {
  while (true) {
    prev = 0;
    pile* p;
    //ddeck();
    p = deck;
    for (p = deck;; ++p) {
      cin >> cd;
      if (cd == "#") return 0;
      p->cards.reset();
      p->cards.push(cd[0], cd[1]);
      p->prev = prev;
      if (prev) prev->next = p;
      prev = p;
      if (p == &deck[51]) break;
    }
    //ddeck();
    p->next = 0;
    p = deck;
    pile* last = 0;
    while (p) {
      pile* m = 0;
      pile* p3 = p;
      if ((p3 = p->prev) && (p3 = p3->prev) && (p3 = p3->prev)) {
        if (p3->cards.topv() == p->cards.topv() || p3->cards.tops() == p->cards.tops()) {
          m = p3;
        }
      }
      pile* p1 = 0;
      if (!m && (p1 = p->prev)) {
        if(p1->cards.topv() == p->cards.topv() || p1->cards.tops() == p->cards.tops()) {
          m = p1;
        }
      }
      if (m) {
        m->cards.push(p->cards.topv(), p->cards.tops());
        p->cards.pop();
        if (!p->cards.size()) {
          p->prev->next = p->next;
          if (p->next) p->next->prev = p->prev;
        }
        p = m;
      } else {
        last = p;
        p = p->next;
      }
    }
    int size = 1;
    p = last;
    while (p->prev) {
      ++size;
      p = p->prev;
    }
    cout << size << " ";
    if (size == 1) cout << "pile";
    else cout << "piles";
    cout << " remaining:";
    while (p) {
      cout << " " << p->cards.size();
      p = p->next;
    }
    cout << endl;
  }
}
