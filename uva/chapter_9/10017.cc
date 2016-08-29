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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

vll a, b, c;
ll m;

void print_vector(char c, vll& v) {
  cout << c << "=>";
  if (!v.empty()) {
    cout << "  ";
    for (auto i : v) cout << " " << i;
  }
  cout << endl;
}

void print_state() {
  print_vector('A', a);
  print_vector('B', b);
  print_vector('C', c);
  cout << endl;
}

bool solve(ll n, vll& a, vll& b, vll& c) {
  if (n == 1) {
    if (m == 0) return true;
    m--;
    c.emplace_back(a.back());
    a.pop_back();
    print_state();
    return false;
  }
  return solve(n - 1, a, c, b) ||
         solve(1, a, b, c) ||
         solve(n - 1, b, a, c);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  ll tc = 0;
  while (cin >> n >> m, n) {
    tc++;
    cout << "Problem #" << tc << endl << endl;
    a.clear(); b.clear(); c.clear();
    for (ll i = n; i >= 1; i--) a.emplace_back(i);
    print_state();
    solve(n, a, b, c);
  }
  // cout << endl;
}
