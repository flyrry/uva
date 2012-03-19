#include <iostream>
#include <stack>

using namespace std;

bool valid(const string& str)
{
  if (str.empty())
    return true;
  stack<char> s;
  s.push(str[0]);
  size_t i(1), length(str.length());
  for (; i < length; ++i) {
    char c = str[i];
    if (c == '(' || c == '[') {
      s.push(c);
      continue;
    }
    if (s.empty())
      return false;
    if (c == ']')
      if (s.top() != '[')
        return false;
      else
        s.pop();
    if (c == ')')
      if (s.top() != '(')
        return false;
      else
        s.pop();
  }
  return s.empty();
}

int main()
{
  ios::sync_with_stdio(false);
  string str;
  getline(cin, str); // discard number of lines
  while (getline(cin, str)) {
#ifdef DEBUG
    cout << "line: " << str << " -> ";
#endif
    cout << (valid(str) ? "Yes" : "No") << endl;
  }
  return 0;
}
