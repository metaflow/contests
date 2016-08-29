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
#include <queue>
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
const int INF = numeric_limits<int>::max();

string AL = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string shift(string s, int k) {
  for (auto &c : s) {
    int v = c - 'A' + 1;
    if (c == ' ') v = 0;
    c = AL[(v + k) % 27];
  }
  return s;
}

vector<string> tokenize(string s) {
  vector<string> r;
  size_t pos = 0;
  while (true) {
    int t = s.find(' ', pos);
    if (t == -1) {
      if (pos < s.size()) r.push_back(s.substr(pos));
      break;
    }
    r.push_back(s.substr(pos, t - pos));
    pos = t + 1;
  }
  return r;
}

int main() {
  // cerr << shift("LINES SHOULD BE AS LONG AS POSSIBLE BUT NOT EXCEEDING CHARACTERS AND NO WORD MAY CROSS A LINEBREAK", 3) << endl;
  set<string> dict;
  string s;
  while (true) {
    cin >> s;
    if (s == "#") break;
    dict.insert(s);
  }
  getline(cin, s);
  getline(cin, s);
  vector<string> best_words;
  int best = 0;
  for (int i = 0; i < 27; ++i) {
    string t = shift(s, i);
    auto words = tokenize(t);
    set<string> matched;
    int c = 0;
    for (auto w : words) {
      if (dict.count(w)) ++c;
    }
    if (c > best) {
      best_words = words;
      best = c;
    }
  }
  string o = "";
  for (auto w : best_words) {
    string t = (o == "" ? w : o + " " + w);
    if (t.size() > 60) {
      cout << o << endl;
      o = w;
      continue;
    }
    o = t;
  }
  cout << o << endl;
}

// time : 38:10
