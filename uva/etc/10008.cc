#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n;
  cin >> n;
  string s;
  getline(cin, s);
  vector<int> counts(26, 0);
  for (int i = 0; i < n; i++) {
    getline(cin, s);
    for (auto c : s) {
      if (!isalpha(c)) continue;
      counts[toupper(c) - 'A']++;
    }
  }
  vector<pair<int, char>> v;
  for (int i = 0; i < 26; i++) v.emplace_back(counts[i], (char)('A' + i));
  sort(v.begin(), v.end(),
    [](const pair<int,char> &a, const pair<int,char> &b) {
      if (a.first != b.first) return a.first > b.first;
      return a.second < b.second;
    });
  for (auto p : v) {
    if (p.first == 0) break;
    printf("%c %d\n", p.second, p.first);
  }
}
