#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

const l SIZE = 26;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s;
  while (cin >> s) {
    l pos = 0;
    l moves = 0;
    for (auto c : s) {
      l t = c - 'a';
      moves += min((t - pos + SIZE) % SIZE, (pos - t + SIZE) % SIZE);
      pos = t;
    }
    cout << moves << endl;
  }
}
