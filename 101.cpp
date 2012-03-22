#include <string>
#include <iostream>

using namespace std;

typedef struct block {
  int n;
  block* above;
  block* below;
} block;

block** blocks = new block*[25];

void move(int a, int b, block** world) {
  blocks[a]->below->above = 0;
  // find last in stack
  block* next = blocks[b];
  while (next->above) next = next->above;
  next->above = blocks[a];
  blocks[a]->below = next;
}

void reset(int b, block** world) {
  block* next = blocks[b]->above;
  while (next) {
    next->below->above = 0;
    // find last in stack
    block* trgt = world[next->n];
    while (trgt->above) trgt = trgt->above;
    trgt->above = next;
    next->below = trgt;
    next = next->above;
    trgt->above->above = 0;
  }
}

void print_world(int n, block** world) {
  for (int i = 0; i < n; ++i) {
    cout << i << ":";
    if (world[i]->above) {
      block* next = world[i]->above;
      while (next) {
        cout << " " << next->n;
        next = next->above;
      }
    }
    cout << endl;
  }
}

bool illegal_cmd(int a, int b, block** world) {
  if (a == b) return true;
  block* ba = blocks[a];
  block* bb = blocks[b];
  block* next = ba->above;
  while (next) {
    if (next->n == b) return true;
    next = next->above;
  }
  next = bb->above;
  while (next) {
    if (next->n == a) return true;
    next = next->above;
  }
  return false;
}

int main(void) {
  size_t n;
  cin >> n;
  block** world = new block*[n];
  for (int i = 0; i < n; ++i) {
    block* b = new block;
    block* pad = new block;
    pad->above = b;
    pad->below = 0;
    b->n = i;
    b->above = 0;
    b->below = pad;
    world[i] = pad;
    blocks[i] = b;
  }

  string cmd;
  while (cin >> cmd) {
    if (cmd == "quit") {
      print_world(n, world);
      return 0;
    }
    int a,b;
    string type;
    cin >> a >> type >> b;
    if (illegal_cmd(a, b, world)) continue;
    if (cmd == "move") {
      if (type == "onto") {
        reset(a, world);
        reset(b, world);
        move(a, b, world);
      } else {
        reset(a, world);
        move(a, b, world);
      }
    } else {
      if (type == "onto") {
        reset(b, world);
        move(a, b, world);
      } else {
        move(a, b, world);
      }
    }
  }

  delete[] world;	
  return 0;
}

