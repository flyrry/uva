#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

typedef int vdata;

struct Vertex 
{
  vdata id;
  int color;
  vector<Vertex*> adj;
  Vertex (vdata id) : id(id), color(-1) {}
};

typedef map<vdata, Vertex*> vmap;
typedef pair<vdata, Vertex*> vpair;

class Graph 
{
  public:
    Graph() {}
    ~Graph();
    void fill();
    Vertex* addVertex (vdata v);
    void addEdge (vdata begin, vdata end, bool directed);
    Vertex* firstVertex();
    Vertex* getVertex (vdata v);
    vmap vertexMap;
    vector<Vertex*> allVertexes;
};

Graph::~Graph()
{
  for (int i = 0; i < allVertexes.size(); ++i)
    delete allVertexes[i];
}

Vertex* Graph::addVertex(vdata v) {
  Vertex* newv = new Vertex(v);
  allVertexes.push_back(newv);
  vertexMap.insert(vpair(v, newv));
  return newv;
}

void Graph::addEdge(vdata begin, vdata end, bool directed = false)
{
  Vertex* v = getVertex(begin);
  Vertex* w = getVertex(end);
  v->adj.push_back(w);
  if (!directed)
    w->adj.push_back(v);
}

Vertex* Graph::getVertex(vdata v)
{
  vmap::iterator it(vertexMap.find(v));

  if (it == vertexMap.end()) {
    return addVertex(v);
  }

  return (*it).second;
}

Vertex* Graph::firstVertex()
{
  return allVertexes[0];
}

void Graph::fill() {
  queue<Vertex*> q;
  Vertex* temp;
  int color = 0;
  for (int i = 0; i < allVertexes.size(); ++i) allVertexes[i]->color = -1;

  for (int i = 0; i < allVertexes.size(); ++i) {
    if (allVertexes[i]->color == -1) {
      ++color;
      while (!q.empty()) q.pop();

      q.push(allVertexes[i]);
      while (!q.empty()) {
        temp = q.front();
        q.pop();

        temp->color = color;
        for (int j = 0; j < temp->adj.size(); ++j) {
          if (temp->adj[j]->color == -1) q.push(temp->adj[j]);
          temp->adj[j]->color = color;
        }
      }
    }
  }
}

int main (void) {
  int cases;
  int computers;
  string input;
  stringstream ss;
  cin >> cases;
  char command;
  int c1, c2;
  Vertex* b;
  Vertex* e;
  int suc_count, unsuc_count;

  while (cases--) {
    Graph* g = new Graph();
    suc_count = unsuc_count = 0;
    cin >> computers;

    for (int i = 1; i <= computers; ++i)
      g->addVertex(i);

    getline(cin,input);
    while (getline(cin,input)) {
      if (!input.size()) break;
      ss << input;
      ss >> command >> c1 >> c2;
      ss.str(string());
      ss.clear();

      if (command == 'c') {
        g->addEdge(c1,c2);
      } else {
        g->fill();
        b = g->getVertex(c1);
        e = g->getVertex(c2);

        if (b->color == e->color) {
          ++suc_count;
        } else {
          ++unsuc_count;
        }
      }
    }

    cout << suc_count << "," << unsuc_count << endl;
    if (cases) cout << endl;

    delete g;
  }

  return 0;
}
