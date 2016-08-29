#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  string s;
  int tc = 0;
  list<string> prefixes;
  bool ok = true;
  while (cin >> s) {
    if (s == "9") {
      tc++;
      if (ok) {
        printf("Set %d is immediately decodable\n", tc);
      } else {
        printf("Set %d is not immediately decodable\n", tc);
      }
      prefixes.clear();
      ok = true;
      continue;
    }
    for (auto u : prefixes) {
      ok = ok && (s.find(u) != 0) && (u.find(s) != 0);
    }
    prefixes.emplace_back(s);
  }
}
