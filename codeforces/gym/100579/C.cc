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
const int MAX = 2001;
const int MOD = 1000000007;

ll DPS[MAX][MAX], DPF[MAX][MAX];

ll S(ll a, ll b) {
  auto &r = DPS[a][b];
  if (r != -1) return r;
  r = 0;
  if (a > 0) r += S(a - 1, b);
  if (b > a) r += S(a, b - 1);
  r %= MOD;
  return r;
}

ll F(ll a, ll b) {
  auto &r = DPF[a][b];
  if (r != -1) return r;
  r = 0;
  if (b > 0) r += F(a, b - 1);
  if (a - 1 > b) r += F(a - 1, b);
  r %= MOD;
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  fill(&DPS[0][0], &DPS[MAX][0], -1);
  fill(&DPF[0][0], &DPF[MAX][0], -1);
  DPS[0][0] = 1;
  DPF[1][0] = 1;
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    string s;
    cin >> s;
    ll a, b;
    sscanf(s.c_str(), "%lld-%lld", &a, &b);
    cout << "Case #" << tc << ": " << F(a, b) << " " << S(b, b) << endl;
  }
}
