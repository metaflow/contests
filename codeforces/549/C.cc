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
  int k, n;
  while (cin >> n >> k) {
    int o = 0;
    for (int i = 0; i < n; i++) {
      int a; cin >> a;
      if (a % 2 == 1) o++;
    }
    int turns = n - k;
    bool last_parity = turns % 2 == 0;
    if (turns == 0) last_parity = (o % 2 == 0);
    bool other_win = false;
    if (o <= turns / 2) {
      other_win = !last_parity;
    }
    if (n - o <= turns / 2) {
      other_win = other_win || last_parity != (k % 2 == 0);
    }
    if (other_win) last_parity = !last_parity;
    if (last_parity) {
      cout << "Daenerys" << endl;
    } else {
      cout << "Stannis" << endl;
    }
  }
}
