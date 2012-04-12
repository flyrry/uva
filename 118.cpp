#include <iostream>
#include <string>

using namespace std;

typedef struct direction {
  int x, y;
  char code;
  direction(int _x,int _y,char _c) : x(_x), y(_y), code(_c) {}
} direction;

typedef struct {
  size_t x, y;
  int orient;
  bool lost;
} robot;

direction* dirs[4];

int get_orient(char c) {
  switch (c) {
    case 'N': return 0;
    case 'E': return 1;
    case 'S': return 2;
    case 'W': return 3;
  }
}

int main(void) {
  // setup directions
  dirs[0] = new direction(0, 1, 'N');
  dirs[1] = new direction(1, 0, 'E');
  dirs[2] = new direction(0, -1, 'S');
  dirs[3] = new direction(-1, 0, 'W');

  size_t x, y, dim_x, dim_y;
  char orient;
  cin >> dim_x >> dim_y;

  int** world = new int*[dim_y+2];
  for (int i = 0; i < dim_y + 2; ++i) {
    world[i] = new int[dim_x+2];
  }

  while (cin >> x >> y >> orient) {
    robot* r = new robot;
    r->x = x;
    r->y = y;
    r->orient = get_orient(orient);
    r->lost = false;
    string seq;
    cin >> seq;
    while (!seq.empty()) {
      switch (seq[0]) {
        case 'L':
          r->orient = (r->orient > 0) ? r->orient - 1 : 3;
          break;
        case 'R':
          r->orient = (r->orient + 1) % 4;
          break;
        case 'F':
          // if gonna fall...
          if (r->x + dirs[r->orient]->x > dim_x ||
              r->y + dirs[r->orient]->y > dim_y) {
            if (world[r->x][r->y]) { // ... and there's scent
              break;
            }
          }
          r->x += dirs[r->orient]->x;
          r->y += dirs[r->orient]->y;
          if (r->x > dim_x || r->y > dim_y) {
            r->lost = true;
            seq.erase();
            // leave scent
            world[r->x - dirs[r->orient]->x][r->y - dirs[r->orient]->y] = 1;
          }
          break;
      }
      seq.erase(0, 1);
    }

    // print self
    if (r->lost) {
      cout << r->x - dirs[r->orient]->x << " "
        << r->y - dirs[r->orient]->y << " "
        << dirs[r->orient]->code << " LOST" << endl;
    } else {
      cout << r->x << " " << r->y << " " << dirs[r->orient]->code << endl;
    }
  }
  return 0;
}
