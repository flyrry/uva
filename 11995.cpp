#include <iostream>
#include <stack>
#include <queue>

using namespace std;

#define STACK           1
#define QUEUE           2
#define PRIORITY_QUEUE  4

int main()
{
  ios::sync_with_stdio(false);

  size_t n;
  while (cin >> n) {
    stack<short> s;
    queue<short> q;
    priority_queue<short> pq;

    short op, x, type;
    type = STACK | QUEUE | PRIORITY_QUEUE;
    while (n--) {
      cin >> op >> x;
      if (op == 1) {
        if (type & STACK)
          s.push(x);
        if (type & QUEUE)
          q.push(x);
        if (type & PRIORITY_QUEUE)
          pq.push(x);
      } else {
        if (type & STACK) {
          if (s.empty() || s.top() != x) type &= ~STACK;
          else s.pop();
        }
        if (type & QUEUE) {
          if (q.empty() || q.front() != x) type &= ~QUEUE;
          else q.pop();
        }
        if (type & PRIORITY_QUEUE) {
          if (pq.empty() || pq.top() != x) type &= ~PRIORITY_QUEUE;
          else pq.pop();
        }
      }
    }

    switch (type) {
      case 3: case 5: case 6: case 7:
        cout << "not sure"; break;
      case STACK:
        cout << "stack"; break;
      case QUEUE:
          cout << "queue"; break;
      case PRIORITY_QUEUE:
          cout << "priority queue"; break;
      default:
          cout << "impossible"; break;
    }
    cout << endl;
  }
  
  return 0;
}
