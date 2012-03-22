#include <iostream>
#include <string>
#include <stack>

using namespace std;

void command(string& from, string& to) {
  //levenshtein distance
  int m = from.size();
  int n = to.size();
  int dp[m+1][n+1];

  for(int i = 0; i <= m; ++i)
    dp[i][0] = i;

  for(int j = 0; j <= n; ++j)
    dp[0][j] = j;

  int cost;
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      cost = (from[i-1] != to[j-1]);
      dp[i][j] = min(dp[i-1][j] + 1, min(dp[i][j-1] + 1, dp[i-1][j-1] + cost));
    }
  }
  // find best path
  int i = m, j = n;
  stack<string> path;
  char cmd[32];
  while (i > 0 && j > 0) {
    if (dp[i-1][j] + 1 == dp[i][j]) {
      sprintf(cmd, "D%c%02d", from[i-1], j+1);
      --i;
    } else if (dp[i][j-1] + 1 == dp[i][j]) {
      sprintf(cmd, "I%c%02d", to[j-1], j);
      --j;
    } else {
      if (from[--i] != to[--j])
        sprintf(cmd, "C%c%02d", to[j], j+1);
      else continue;
    }
    path.push(string(cmd));
  }
  while (i > 0) {
    sprintf(cmd, "D%c%02d", from[--i], 1);
    path.push(string(cmd));
  }
  while (j > 0) {
    sprintf(cmd, "I%c%02d", to[j-1], j);
    --j;
    path.push(string(cmd));
  }
  while (!path.empty()) {
    cout << path.top();
    path.pop();
  }
  cout << "E" << endl;
}

int main(void) {
  string from,to;
  while (cin >> from) {
    if (from == "#") return 0;
    cin >> to;
    command(from,to);
  }
}
