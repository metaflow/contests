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
  string a, b;
  while (cin >> a >> b) {
    vi counts(150);
    for (auto c : b) counts[int(c)]++;
    if (a.size() % 2 != 0) a += "!";
    reverse(a.begin(), a.end());
    string _ = "";
    for (size_t i = 0; i < a.size(); i+=2) {
      int I = min(counts[a[i + 1]], 3);
      int V = min(counts[a[i]], 1);
      int X = min((i == 0) ? 0 : counts[a[i - 1]], 1);
      if (V + I >= 3) {
        while (V--) {
          _ += a[i];
          counts[a[i]]--;
        }
        while (I--) {
          _ += a[i + 1];
          counts[a[i + 1]]--;
        }
        continue;
      }
      if (X > 0 && I > 0) {
        _ += a[i + 1];
        counts[a[i + 1]]--;
        _ += a[i - 1];
        counts[a[i - 1]]--;
        continue;
      }
      while (V--) {
        _ += a[i];
        counts[a[i]]--;
      }
      while (I--) {
        _ += a[i + 1];
        counts[a[i + 1]]--;
      }
    }
    cout << _ << endl;
  }
}
