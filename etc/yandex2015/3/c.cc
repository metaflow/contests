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

const int MAX = 5000;

bool field[MAX][MAX];

// O(N) for each element v[i] get length of max span of [a, b]:
// each p in [a, b] is not less then v[i]. It's possible to get [a, b] itself
vi lower_bound_ranges(vector<int> &v) {
  stack<int> less;
  int n = v.size();
  vi w(n, 1);
  less.push(-1);
  for (int i = 0; i < n; i++) {
    while (less.top() != -1 && !(v[less.top()] < v[i])) less.pop();
    w[i] += i - less.top() - 1;
    less.push(i);
  }
  while (!less.empty()) less.pop();
  less.push(n);
  for (int i = n - 1; i > -1; i--) {
    while (less.top() != n && !(v[less.top()] < v[i])) less.pop();
    w[i] += less.top() - i - 1;
    less.push(i);
  }
  return w;
}

template <typename Iterator>
ostream& print_range(ostream& s, const Iterator a, const Iterator b) {
  bool first = true;
  for (auto i = a; i != b; i++) {
    if (!first) s << " ";
    first = false;
    s << *i;
  }
  return s;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int m, n, k;
  cin >> m >> n;
  fill(&field[0][0], &field[MAX][0], false);
  cin >> k;
  int best = 0;
  for (int i = 0; i < k; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    if (x2 < x1) swap(x1, x2);
    if (y2 < y1) swap(y1, y2);
    best = max(best, (x2 - x1) * (y2 - y1));
    for (int x = max(x1 - 1, 0); x <= min(x2, m - 1); x++) {
      for (int y = max(y1 - 1, 0); y <= min(y2, n - 1); y++) {
        field[x][y] = true;
      }
    }
  }
  vi row(n, 0);
  for (int x = 0; x < m; x++) {
    for (int y = 0; y < n; y++) {
      if (field[x][y]) {
        row[y] = 0;
      } else {
        row[y]++;
      }
    }
    vi d = lower_bound_ranges(row);
    // print_range(cout, row.begin(), row.end()) << endl;
    // print_range(cout, d.begin(), d.end()) << endl << endl;
    for (size_t i = 0; i < row.size(); i++) {
      best = max(best, row[i] * d[i]);
    }
  }
  cout << best << endl;
}
