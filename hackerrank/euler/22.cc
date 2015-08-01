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
  int n; cin >> n;
  map<string, int> names;
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    names[s] = 0;
  }
  int i = 0;
  for (auto &e : names) {
    i++;
    int v = 0;
    for (auto c : e.first) v += c - 'A' + 1;
    e.second = v * i;
  }
  int q; cin >> q;
  while (q--) {
    string s; cin >> s;
    cout << names[s] << endl;
  }
}
