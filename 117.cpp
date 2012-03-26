#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

struct edge {
  int to;
  int w;
  edge(int _n, int _w) : to(_n), w(_w) {}
};

struct node {
  int id;
  int dist;
  bool visited;
  bool operator<(const node& n) const { return dist > n.dist; }
};

int main(void) {
  map<int, node> nodes;
  map<int, vector<edge> > edges;
  string str;
  int sum = 0;
  while (cin >> str) {
    if (str != "deadend") {
      char f, t;
      f = str[0];
      t = str[str.size()-1];
      nodes[f].dist = 0x7fffffff;
      nodes[f].visited = false;
      nodes[f].id = f;
      nodes[t].dist = 0x7fffffff;
      nodes[t].visited = false;
      nodes[t].id = t;
      edges[f].push_back(edge(t, str.size()));
      edges[t].push_back(edge(f, str.size()));
      sum += str.size();
    } else {
      // find odd nodes
      int s = -1;
      int e = -1;
      int dij = 0;
      for (map<int, vector<edge> >::iterator i(edges.begin()), end(edges.end()); i != end; ++i) {
        if (i->second.size() % 2) {
          if (s == -1) s = i->first;
          else e = i->first;
        }
      }
      if (s != -1) {
        // dijkstra
        priority_queue<node> q;
        nodes[s].dist = 0;
        nodes[s].visited = true;
        q.push(nodes[s]);
        while (!q.empty()) {
          node n = q.top();
          if (n.id == e) {
            dij = n.dist;
            break;
          }
          nodes[n.id].visited = true;
          q.pop();
          for (vector<edge>::iterator i(edges[n.id].begin()), end(edges[n.id].end()); i != end; ++i) {
            if (nodes[i->to].visited) continue;
            if (nodes[i->to].dist > n.dist + i->w) nodes[i->to].dist = n.dist + i->w;
            q.push(nodes[i->to]);
          }
        }
      }
      cout << dij + sum << endl;
      sum = 0;
      edges.clear();
      nodes.clear();
    }
  }
  return 0;
}
