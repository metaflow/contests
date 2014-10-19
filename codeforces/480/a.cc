#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n;
  while (cin >> n) {
    vector<ii> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].first >> v[i].second;
    sort(v.begin(), v.end());
    int today = 0;
    for (auto p : v) {
      if (p.second >= today) {
        today = p.second;
        continue;
      }
      today = p.first;
    }
    cout << today << endl;
  }
}
