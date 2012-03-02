#include <iostream>
#include <list>
#include <algorithm>
#include <functional>

using namespace std;

#define INVALID_POINT 9999.9

typedef struct {
  double tlx, tly, brx, bry; // top-left x,y and bottom-right x,y
  size_t id;
} rect;

typedef struct {
  double x, y;
} point;

bool hit_test(rect& r, point& p)
{
  if (p.x < r.brx &&
      p.x > r.tlx &&
      p.y < r.bry &&
      p.y > r.tly)
    return true;
  return false;
}

int main()
{
  ios::sync_with_stdio(false);
  char type;
  list<rect> rectangles;
  rect r;
  point p;
  for (;;) {
    cin >> type;
    size_t r_idx = 1, p_idx = 1;
    if (type == 'r') {
      cin >> r.tlx >> r.tly >> r.brx >> r.bry;
      r.id = r_idx;
      rectangles.push_back(r);
      ++r_idx;
    } else {
      cin >> p.x >> p.y;
      if (p.x == INVALID_POINT &&
          p.y == INVALID_POINT) {
        break;
      } else {
        // test which rectangles contain this point
        list<rect>::iterator it = rectangles.begin();
        bool found = false;
        while ((it = find_if(it, rectangles.end(), bind2nd(ptr_fun(hit_test), p))) != rectangles.end()) {
          cout << "Point " << p_idx << " is contained in figure " << it->id << endl;
          found = true;
          it++;
        }
        if (!found)
          cout << "Point " << p_idx << " is not contained in any figure" << endl;
      }
      ++p_idx;
    }
  }

  return 0;
}
