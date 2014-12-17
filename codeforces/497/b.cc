#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vit = vector<int>::iterator;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 100010;

vi sum1;
vi sum2;
int s1, s2, latest;
bool ok;

void check(int n, int c, int t) {
  // cerr << "at " << t << endl;
  if (c == n) return;
  int d1 = lower_bound(sum1.begin(), sum1.end(), sum1[c] + t)-sum1.begin();
  int d2 = lower_bound(sum2.begin(), sum2.end(), sum2[c] + t)-sum2.begin();
  // cerr << ":" << d1 << " " << d2 << endl;
  if (d1 == d2) {
    // cerr << "both not found" << d1 << " " << d2 << endl;
    ok = false;
    return;
  }
  if (d2 < d1) {
    s2++;
    latest = s2;
    check(n, d2, t);
  } else {
    s1++;
    latest = s1;
    check(n, d1, t);
  }
}

int main() {
  int n;
  while (cin >> n) {
    sum1.resize(n + 1);
    sum1[0] = 0;
    sum2.resize(n + 1);
    sum2[0] = 0;
    for (int i = 1; i <= n; i++) {
      int who;
      cin >> who;
      sum1[i] = sum1[i - 1];
      sum2[i] = sum2[i - 1];
      if (who == 1) {
        sum1[i]++;
      } else {
        sum2[i]++;
      }
    }
    vector<ii> solutions;
    for (int t = 1; t <= max(sum1[n], sum2[n]); t++) {
      s1 = 0; s2 = 0; ok = true;
      check(n, 0, t);
      // cerr << "check " << t << " " << ok << " " << s1 << " " << s2 << endl;

      if (ok && (s1 != s2) && max(s1, s2) == latest) {
        solutions.emplace_back(latest, t);
      }
    }
    sort(solutions.begin(), solutions.end());
    cout << solutions.size() << endl;
    for (auto s : solutions) {
      cout << s.first << " " << s.second << endl;
    }
    // return 0;
  }
}
