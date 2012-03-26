#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

char maze[30][80];
int x, y;

void bfs() {
  queue<pair<int,int> > q;
  q.push(make_pair(x, y));
  while (!q.empty()) {
    int i, j;
    i = q.front().first;
    j = q.front().second;
    q.pop();
    maze[i][j] = '#';
    if (i-1 >= 0 && maze[i-1][j] == ' ') {
      maze[i-1][j] = '#';
      q.push(make_pair(i-1,j));
    }
    if (i+1 < 30 && maze[i+1][j] == ' ') {
      maze[i+1][j] = '#';
      q.push(make_pair(i+1,j));
    }
    if (j-1 >= 0 && maze[i][j-1] == ' ') {
      maze[i][j-1] = '#';
      q.push(make_pair(i,j-1));
    }
    if (j+1 < 80 && maze[i][j+1] == ' ') {
      maze[i][j+1] = '#';
      q.push(make_pair(i,j+1));
    }
  }
}

int main(void) {
  int n;
  cin >> n;
  string line;
  getline(cin, line);
  while (n--) {
    for (int i = 0; i < 30; ++i) {
      for (int j = 0; j < 80; ++j) {
        maze[i][j] = 'r';
      }
    }
    int j = 0;
    while (getline(cin, line)) {
      if (line[0] == '_') {
        bfs();
        for (int i = 0; i < 30; ++i) {
          for (int j = 0; j < 80; ++j) {
            if (maze[i][j] == 'r') break;
            cout << maze[i][j];
          }
          if (maze[i][0] == 'r') break;
          cout << endl;
        }
        cout << line << endl;
        break;
      } else {
        for (int i = 0; i < line.size(); ++i) {
          maze[j][i] = line[i];
          if (line[i] == '*') {
            x = j;
            y = i;
          }
        }
        ++j;
      }
    }
  }
  return 0;
}

