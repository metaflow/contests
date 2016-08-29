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

const int MAX = 12;

struct dpe {
  ll cost;
  int split;
};

vll values;
dpe DP[MAX][MAX];

dpe dp(int f, int t) {
  auto &r = DP[f][t];
  if (r.cost == -1) {
    if (t - f == 1) {
      r.split = f;
      r.cost = 0;
      return r;
    }
    r.cost = INF;
    ll part = values[f] * values[t];
    for (ll i = f + 1; i < t; i++) {
      ll q = part * values[i] + dp(f, i).cost + dp(i, t).cost;
      if (r.cost > q) {
        r.cost = q;
        r.split = i;
      }
    }
  }
  return r;
}

void print_solution(int f, int t) {
  auto e = DP[f][t];
  if (e.cost == 0) {
    cout << "A" << f + 1;
    return;
  }
  cout << "(";
  print_solution(f, e.split);
  cout << " x ";
  print_solution(e.split, t);
  cout << ")";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, tc = 0;
  while (cin >> n, n) {
    tc++;
    dpe e;
    e.cost = -1;
    fill(&DP[0][0], &DP[MAX][0], e);
    n++;
    values.clear();
    values.resize(n);
    cin >> values[0];
    cin >> values[1];
    int _;
    for (int i = 2; i < n; i++) cin >> _ >> values[i];
    dp(0, n - 1);
    cout << "Case " << tc << ": ";
    print_solution(0, n - 1);
    cout << endl;
  }
}
