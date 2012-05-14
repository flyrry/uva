#include <iostream>

using namespace std;

#define MAX_PIRATES 1024100 // some safety space :p

bool pirates[MAX_PIRATES];

#define LEFT(n)   ((n << 1) + 1)
#define RIGHT(n)  ((n << 1) + 2)

//#define DEBUG

typedef struct {
  int from, to, center, value;
  char op;
} node_t;

node_t nodes[MAX_PIRATES << 2];

void init(int n, int from, int to) {
  node_t& node = nodes[n];
  node.from = from;
  node.to = to;
  node.center = (from + to) / 2;
  node.op = 'N'; // no convertion has been done yet

  if (from != to) {
    init(LEFT(n), node.from, node.center);
    init(RIGHT(n), node.center + 1, node.to);
    node.value = nodes[LEFT(n)].value + nodes[RIGHT(n)].value;
  } else {
    node.value = pirates[from];
  }
}

// sets the operation flag without actually performing any tree updates
inline void convert(node_t& node, char op) {
  if (op == 'I') {
    switch (node.op) { // invert current pending operation
      case 'N':
        node.op = 'I'; break;
      case 'E':
        node.op = 'F'; break;
      case 'F':
        node.op = 'E'; break;
      case 'I':
        node.op = 'N'; break;
    }
  } else { // 'F' or 'E' or 'N'
    node.op = op;
  }
}

// calculate number of buccaneer pirates
// this is a fast operation as only one tree level is updated
inline void update(int n) {
  node_t& node = nodes[n];

  switch (node.op) {
    case 'N':
      return; // this node has no convertion pending
    case 'E':
      node.value = 0; // all are now barbary
      break;
    case 'F':
      node.value = node.to - node.from + 1; // all are now buccaneers
      break;
    case 'I':
      node.value = node.to - node.from + 1 - node.value;
      break;
  }

  // prepare for update to segments of this interval
  convert(nodes[LEFT(n)], node.op);
  convert(nodes[RIGHT(n)], node.op);
  node.op = 'N'; // convertion is finished, this tree level updated
}

void perform_operation(int n, int from, int to, char op) {
  node_t& node = nodes[n];

  bool full_coverage = from <= node.from && to >= node.to;

  if (full_coverage) { // this node's interval is fully covered by convert operation
#ifdef DEBUG
    cout << "converting (" << from << "[" << node.from << " " << node.to << "]" << to << ")" << endl;
#endif
    convert(node, op);
  }
  // update nodes on the way
  update(n);

  if (from > node.to || to < node.from) return; // operation interval is outside node interval's bounds
  // update is always before this cut-off, since there may be nodes that were outside bounds before 
  // and had operation pushed on them and it would get overwritten if we don't update

  if (!full_coverage) {
    // update children (one of the queries will return immediately -> possible optimization?)
    perform_operation(LEFT(n), from, to, op);
    perform_operation(RIGHT(n), from, to, op);
    node.value = nodes[LEFT(n)].value + nodes[RIGHT(n)].value; // update current node since children got updated
  }
}

int query(int n, int from, int to) {
  update(n);
  node_t& node = nodes[n];
  if (from > node.to || to < node.from) return 0; // query outside bounds
  if (from <= node.from && to >= node.to) return node.value; // query fully covers this interval

  // partial coverage
#ifdef DEBUG
  int left = query(LEFT(n), from, to);
  int right = query(RIGHT(n), from, to);
  cout << "summing " << nodes[LEFT(n)].from << " " << nodes[LEFT(n)].to << "(" << left << ")" << " and "
    << nodes[RIGHT(n)].from << " " << nodes[RIGHT(n)].to << "(" << right << ")" << endl;
  return left + right;
#else
  return query(LEFT(n), from, to) + query(RIGHT(n), from, to);
#endif
}

#ifdef DEBUG
void debug() {
  queue<pair<int,int> > bfsq;
  int level = 0;
  for (bfsq.push(make_pair(0,0)); !bfsq.empty(); bfsq.pop()) {
    node_t& n = nodes[bfsq.front().first];
    if (level != bfsq.front().second) {
      level = bfsq.front().second;
      cout << endl;
    }
    cout << "[" << n.from << " " << n.to << "](" << n.op << " " << n.value << ")";
    if (n.from == n.to) continue;
    bfsq.push(make_pair(LEFT(bfsq.front().first), bfsq.front().second + 1));
    bfsq.push(make_pair(RIGHT(bfsq.front().first), bfsq.front().second + 1));
  }
  cout << endl;
}

void debug_pirates(int n) {
    for (int p(0); p < n; ++p)
      cout << (pirates[p] ? "1" : "0") << " ";
    cout << endl;
}
#endif

int main()
{
  ios::sync_with_stdio(false);
  int cases;
  cin >> cases;
  for (int i(1); i <= cases; ++i) {
    cout << "Case " << i << ":\n";

    // build pirate land
    int sets, queries, repeat, from, to, q = 0, pp = 0;
    string pirates_str;
    char op;
    cin >> sets;
    for (int s(0); s < sets; ++s) {
      cin >> repeat;
      cin >> pirates_str;
      size_t sz(pirates_str.size());
      while (repeat--) {
        for (size_t p(0); p < sz; ++p) {
          pirates[pp++] = (pirates_str[p] == '1');
        }
      }
    }
    init(0, 0, pp - 1);

    cin >> queries;
#ifdef DEBUG
    debug_pirates(pp-1);
#endif
    while (queries--) {
      cin >> op >> from >> to;
#ifdef DEBUG
      debug();
#endif
      if (op == 'S') cout << "Q" << ++q << ": " << query(0, from, to) << '\n';
      else perform_operation(0, from, to, op);
    }
  }
  
  return 0;
}
