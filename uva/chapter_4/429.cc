#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int MAX = 200;
const int INF = numeric_limits<int>::max() / 2;

int d[MAX][MAX];

void FloydWarshall(int n) {
  for (int k = 0; k < n; ++k)
  for (int i = 0; i < n; ++i)
  for (int j = 0; j < n; ++j)
    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

int distance(const string &a, const string &b) {
  int result = 0;
  if (a.size() != b.size()) return INF;
  for (int i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) ++result;
  }
  return result;
}

int main() {
  int tcc;
  cin >> tcc;
  string s;
  getline(cin, s); getline(cin, s);
  while (tcc--) {
    map<string, int> words;
    int i = 0;
    while (true) {
      getline(cin, s);
      if (s == "*") break;
      words[s] = i++;
    }
    fill(&d[0][0], &d[MAX][0], INF);
    for (auto a : words) {
      for (auto b : words) {
        if (distance(a.first, b.first) != 1) continue;
        d[a.second][b.second] = d[b.second][a.second] = 1;
      }
    }
    FloydWarshall(words.size());
    while (true) {
      getline(cin, s);
      if (s.empty()) break;
      string start = s.substr(0, s.find(" "));
      string end = s.substr(s.find(" ") + 1);
      cout << s << " " << d[words[start]][words[end]] << endl;
    }
    if (tcc) cout << endl;
  }
}
