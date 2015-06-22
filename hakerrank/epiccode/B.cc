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
  ll n; cin >> n;
  string s; cin >> s;
  vll count(26);
  ll sum = 0;
  for (auto c : s) {
    count[c - 'a']++;
    sum += count[c - 'a'];
  }
  cout << sum << endl;
}
