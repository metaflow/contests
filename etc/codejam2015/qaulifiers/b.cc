#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 1001;
int p[MAX];

int s(int t) {
  if (t == 0) return 0;
  if (p[t] == 0) return s(t - 1);
  if (t == 1) return 1;
  if (p[t] == 0) return s(t - 1);
  int a = t / 2;
  p[t]--;
  p[a]++;
  p[t - a]++;
  return min(t, 1 + s(t));
}

int f(int t, vi& values) {
  if (t == 1) return 1;
  if (values[t] == 0) return f(t - 1, values);
  //split
  vi c(values);
  int a = t / 2;
  c[t]--;
  c[a]++;
  c[t - a]++;
  int b = 1 + f(t, c);
  // or shift
  vi d(values);
  d.erase(d.begin());
  return min(b, 1 + f(t - 1, d));
}

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    fill_n(p, MAX, 0);
    vi v(MAX, 0);
    while (n--) {
      int a; cin >> a;
      p[a]++;
      v[a]++;
    }
    int a = s(MAX - 1);
    // int b = f(MAX - 1, v);
    printf("Case #%d: %d\n", tc, a);
    // if (a != b) printf("<<<\n");
  }
}
