#include <iostream>
#include <queue>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  priority_queue<size_t, vector<size_t>, greater<size_t> > sequence;
  size_t N, n, m;
  for (;;) {
    cin >> N;
    if (!N) break;
    while (N--) {
      cin >> n;
      sequence.push(n);
    }
    size_t cost = 0;
    while (sequence.size() > 1) {
      n = sequence.top(); sequence.pop();
      m = sequence.top(); sequence.pop();
      cost += n + m;
      sequence.push(n + m);
    }
    sequence.pop(); // clear the pq;
    cout << cost << endl;
  }
  return 0;
}
