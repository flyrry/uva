#include <iostream>
#include <map>
#include <vector>

typedef long long llong;

using namespace std;
map<llong, size_t> m;
vector<llong> o;

int main(void) {
	llong n;
	while (cin >> n) {
		if (!m[n]) o.push_back(n);
		++m[n];
	}
	for (vector<llong>::iterator i(o.begin()), end(o.end()); i != end; ++i) {
		cout << *i << " " << m[*i] << endl;
	}
	return 0;
}

