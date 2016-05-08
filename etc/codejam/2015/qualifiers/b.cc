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
  if (t == 1) return 1;
  if (p[t] == 0) return s(t - 1);
  int best = t;
  int last_size = 0;
  for (int cuts = 1; cuts < min(t, 3); cuts++) {
    int size = t / (cuts + 1);
    if (size == last_size) continue;
    last_size = size;
    int b = t % size;
    int n = t / size;
    if (b == 0) {
      p[size] += n * p[t];
      best = min(best, cuts * p[t] + s(t - 1));
      p[size] -= n * p[t];
      continue;
    }
    p[size] += n * p[t];
    p[b] += p[t];
    best = min(best, cuts * p[t] + s(t - 1));
    p[size] -= n * p[t];
    p[b] -= p[t];
  }
  return best;
}

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    cerr << "." << endl;
    int n; cin >> n;
    fill_n(p, MAX, 0);
    vi v(MAX, 0);
    while (n--) {
      int a; cin >> a;
      p[a]++;
      v[a]++;
    }
    int a = s(MAX - 1);
    printf("Case #%d: %d\n", tc, a);
  }
}
