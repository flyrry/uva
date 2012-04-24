#include <iostream>

using namespace std;

void skip_subtree(const string& tree, int& pos) {
  if (tree[++pos] == 'p') skip_subtree(tree, pos);
  if (tree[++pos] == 'p') skip_subtree(tree, pos);
  if (tree[++pos] == 'p') skip_subtree(tree, pos);
  if (tree[++pos] == 'p') skip_subtree(tree, pos);
  ++pos;
}

void attach_subtree(const string& tree, int& pos, string& result) {
  result += 'p';
  for (int i(0); i < 4; ++i) {
    if (tree[++pos] == 'p') attach_subtree(tree, pos, result);
    else {
      result += tree[pos];
    }
  }
  ++pos;
}

int count_pixels(const string& tree, int& pos, int factor) {
  int sum = 0;
  for (int i(0); i < 4; ++i) {
    if (tree[++pos] == 'p') sum += count_pixels(tree, pos, factor >> 2);
    else if (tree[pos] == 'f') sum += factor;
  }
  return sum;
}

int main()
{
  ios::sync_with_stdio(false);
  int cases;
  cin >> cases;
  while (cases--) {
    string ltree, rtree;
    cin >> ltree >> rtree;

    string result;
    for (int l(0), r(0), lsz(ltree.size()), rsz(rtree.size()); l < lsz && r < rsz;) {
      if (ltree[l] == rtree[r]) {
        result += ltree[l];
        ++l;
        ++r;
      } else if (ltree[l] == 'f') {
        result += 'f';
        ++l;
        // skip right subtree
        if (rtree[r] == 'p')
          skip_subtree(rtree, r);
        else ++r;
      } else if (rtree[r] == 'f') {
        result += 'f';
        ++r;
        // skip left subtree
        if (ltree[l] == 'p')
          skip_subtree(ltree, l);
        else ++l;
      } else if (ltree[l] == 'p' /*&& rtree[r] == 'e'*/) {
        attach_subtree(ltree, l, result);
        ++r;
      } else if (rtree[r] == 'p' /*&& ltree[l] == 'e'*/) {
        attach_subtree(rtree, r, result);
        ++l;
      }
    }

    int start = 0;
    cout << "There are ";
    if (result[0] == 'p') cout << count_pixels(result, start, 1024 >> 2);
    else if (result == "f") cout << "1024";
    else cout << "0";
    cout << " black pixels." << endl;;
  }
  return 0;
}
