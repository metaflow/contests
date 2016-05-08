#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    map<ll, ll> freq;
    ll p; cin >> p;
    vll elements(p);
    for (int i = 0; i < p; i++) cin >> elements[i];
    for (int i = 0; i < p; i++) cin >> freq[elements[i]];
    multiset<ll> answer;
    while (true) {
      ll v = 0;
      for (auto e : freq) {
        if (e.first == 0 || e.second == 0) continue;
        v = e.first;
        auto c = freq;
        bool ok = true;
        if (v > 0) {
          for (auto a = c.begin(); a != c.end(); a++) {
            if (a->second == 0) continue;
            ll t = a->first + v;
            if (c.count(t) == 0) {
              ok = false;
              break;
            }
            c[t] -= a->second;
            if (c[t] < 0) {
              ok = false;
              break;
            }
          }
        } else {
          for (auto a = c.rbegin(); a != c.rend(); a++) {
            if (a->second == 0) continue;
            ll t = a->first + v;
            if (c.count(t) == 0) {
              ok = false;
              break;
            }
            c[t] -= a->second;
            if (c[t] < 0) {
              ok = false;
              break;
            }
          }
        }
        if (ok) {
          freq = c;
          answer.insert(v);
          break;
        }
      }
      if (v == 0) break;
    }
    while (freq[0] > 1) {
      answer.insert(0);
      freq[0] = (freq[0] >> 1);
    }

    cout << "Case #" << tc << ":";
    for (auto i : answer) cout << " " << i;
    cout << endl;
  }
}
