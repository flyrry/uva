#include <iostream>
#include <list>
#include <cstring>
#include <map>
#include <set>
#include <algorithm>
#include <limits.h>

using namespace std;

class shape;

typedef pair<int, int> point;
typedef list<point> point_list;
typedef map<int, int> strands;
typedef map<int, shape*> shape_map;
typedef set<shape*> unique_shapes;

static int field[100][100];

#ifdef DEBUG_BS
void print_shape(pair<const int, shape*>& ks);
void print_unique_shape(const shape* s);
#endif

class shape {
  static int _shape_id_next;
  public:
  bool points[100][100];
  int id;
  int width, height;
  int min_x, min_y, max_x, max_y;
  string footprint;

  shape(int x, int y) : min_x(INT_MAX), min_y(INT_MAX), max_x(0), max_y(0), width(0), height(0)
  {
    memset(points, false, sizeof(bool) * 100 * 100);
    id = ++_shape_id_next;
    add(x, y);
  }

  void add(int x, int y)
  {
    points[x][y] = true;
    min_x = min(min_x, x);
    min_y = min(min_y, y);
    max_x = max(max_x, x);
    max_y = max(max_y, y);
  }

  void combine(shape& other)
  {
    for (int x = other.min_x; x <= other.max_x; ++x) {
      for (int y = other.min_y; y <= other.max_y; ++y) {
        if (other.points[x][y])
          points[x][y] = other.points[x][y];
      }
    }
    min_x = min(min_x, other.min_x);
    max_x = max(max_x, other.max_x);
    min_y = min(min_y, other.min_y);
    max_y = max(max_y, other.max_y);
  }

  void normalize()
  {
    width = max_x - min_x + 1;
    height = max_y - min_y + 1;

    for (int x = 0; x < width; ++x) {
      for (int y = 0; y < height; ++y) {
        points[x][y] = points[x+min_x][y+min_y];
      }
    }
  }

  void rotate()
  {
    bool temp[100][100];
    memcpy(temp, points, sizeof(bool) * 100 * 100);

    swap(width, height);

    footprint.clear();
    for (int x = 0; x < width; ++x) {
      for (int y = 0; y < height; ++y) {
        bool on = temp[y][width-x-1];
        points[x][y] = on;
        if (on) {
          footprint.push_back('0'+x);
          footprint.push_back('0'+y);
        }
      }
    }
  }

  void flip()
  {
    footprint.clear();
    for (int x = 0; x < width; ++x) {
      for (int y = 0; y < height; ++y) {
        if (y < height/2)
          swap(points[x][y], points[x][height-y-1]);
        if (points[x][y]) {
          footprint.push_back('0'+x);
          footprint.push_back('0'+y);
        }
      }
    }
  }

  void compute_hash() {
    list<string> footprints;

    normalize();
    for (int flips = 0; flips < 2; ++flips) {
      for (int rots = 0; rots < 4; ++ rots) {
        rotate();
        footprints.push_back(footprint);
      }
      flip();
    }
    footprints.sort();
    footprint = footprints.front();
  }
};

int shape::_shape_id_next = 1;

void build_shapes(point_list& points, shape_map& shapes, unique_shapes& uniques) {
  points.sort();
  int x,y;

  for (point_list::iterator it(points.begin()), end(points.end()); it != end; ++it) {
    x = it->first;
    y = it->second;
#ifdef DEBUG_BS
    cerr << it->first << " " << it->second << endl;
#endif
    int above = 0, left = 0;

    // check top
    if (y) // y-1 >= 0
      above = field[x][y-1];
    if (above) {
#ifdef DEBUG_BS
      cerr << "shape above!" << endl;
#endif
      // include this point into shape found above
      field[x][y] = above;
      shapes[above]->add(x, y);
    }

    // check left
    if (x) //(x-1 >= 0)
      left = field[x-1][y];
    if (left) {
#ifdef DEBUG_BS
      cerr << "shape on the left!" << endl;
#endif
      if (above) {
        if (shapes[above] != shapes[left]) {
        //if (above != left) {
#ifdef DEBUG_BS
          cerr << "combining!" << endl;
#endif
          // there was a different shape above as well
          // ==> fuse two shapes together
          shapes[above]->combine(*shapes[left]);
          // overwrite
          shape* s = shapes[left];
          uniques.erase(shapes[left]);
          delete s;
          shapes[left] = shapes[above];
        }
      } else {
        // include this point into shape to the left
        field[x][y] = left;
        shapes[left]->add(x, y);
      }
    }

#ifdef DEBUG_BS
    cerr << "above: " << above << " left: " << left << endl;
#endif
    if (!above && !left) { // no adjacent shapes, create new one
      shape* s = new shape(x,y);
      uniques.insert(s);
      field[x][y] = s->id;
      shapes[s->id] = s;
    }
  }
}

#ifdef DEBUG_BS
void print_shape(pair<const int, shape*>& ks) {
  shape* s = ks.second;
  cerr << "id: " << s->id << "[" << ks.first << "]\t";
  cerr << "width: " << s->width << " height: " << s->height;
  cerr << endl;
}

void print_unique_shape(const shape* s) {
  cerr << "id: " << s->id << "\t";
  cerr << "width: " << s->width << " height: " << s->height;
  cerr << " footprint: " << s->footprint;
  cerr << endl;
  for (int y = 0; y < s->height; ++y) {
    for (int x = 0; x < s->width; ++x) {
      cout << (char)(s->points[x][y] ? 'X' : 'O');
    }
    cout << endl;
  }
}
#endif

int main()
{
  ios::sync_with_stdio(false);
  point_list original_points, equiv_points;
  shape_map original_shapes, equiv_shapes;
  unique_shapes original_uniques, equiv_uniques;

  int cases;
  cin >> cases;
  int w, h, n, x, y;
  int i;

  while (cases--) {
    original_shapes.clear();
    original_uniques.clear();
    equiv_shapes.clear();
    equiv_uniques.clear();

    memset(field, 0, sizeof(int) * 100 * 100);

    cin >> w >> h >> n;

    // read first board
    for (i = 0; i < n; ++i) {
      cin >> x >> y;
      original_points.push_back(make_pair(x, y));
    }

    // read second board
    for (i = 0; i < n; ++i) {
      cin >> x >> y;
      equiv_points.push_back(make_pair(x, y));
    }

    // build shapes
    build_shapes(original_points, original_shapes, original_uniques);
    original_points.clear();

    memset(field, 0, sizeof(int) * 100 * 100);

    // build shapes
    build_shapes(equiv_points, equiv_shapes, equiv_uniques);
    equiv_points.clear();

#ifdef DEBUG_BS
    cerr << "# of original shapes: " << original_shapes.size() << endl;
    for_each(original_shapes.begin(), original_shapes.end(), print_shape);
    cerr << "# of equivalent shapes: " << equiv_shapes.size() << endl;
    for_each(equiv_shapes.begin(), equiv_shapes.end(), print_shape);
#endif

    // compare
    if (original_uniques.size() != equiv_uniques.size()) {
      cout << "NO" << endl;
      continue;
    }

    for_each(original_uniques.begin(), original_uniques.end(), mem_fun(&shape::compute_hash));
    for_each(equiv_uniques.begin(), equiv_uniques.end(), mem_fun(&shape::compute_hash));

#ifdef DEBUG_BS
    cerr << "# of unique shapes: " << original_uniques.size() << endl;
    for_each(original_uniques.begin(), original_uniques.end(), print_unique_shape);
    cerr << "# of equivalent unique shapes: " << equiv_uniques.size() << endl;
    for_each(equiv_uniques.begin(), equiv_uniques.end(), print_unique_shape);
#endif
    
    bool match_found = true;
    for (unique_shapes::iterator it(original_uniques.begin()), end(original_uniques.end()); it != end; ++it) {
      match_found = false;
      for (unique_shapes::iterator eit(equiv_uniques.begin()), eend(equiv_uniques.end()); eit != eend; ++eit) {
        if ((*it)->footprint == (*eit)->footprint)
        {
          match_found = true;
          equiv_uniques.erase(eit);
          break;
        }
      }
      if (!match_found) {
        break;
      }
    }

    while (!original_uniques.empty()) {
      delete *original_uniques.begin();
      original_uniques.erase(original_uniques.begin());
    }

    if (!match_found) {
      cout << "NO" << endl;
      continue;
    }

    cout << "YES" << endl;
  }
  return 0;
}
