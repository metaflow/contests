#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n;

  while (cin >> n) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    bool f = true;
    int count = 0;
    while (f) {
      f = false;
      for (int i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) {
          swap(v[i], v[i + 1]);
          f = true;
          count++;
        }
      }
    }
    printf("Minimum exchange operations : %d\n", count);
  }

/*  while (cin >> n) {
    vector<ii> v(n);
    for (int i = 0; i < n; i++) {
      cin >> v[i].first;
      v[i].second = i;
    }
    sort(v.begin(), v.end());
    int at = 0;
    int sh = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
      if (v[i].second + sh <= i) continue;
      count += (v[i].second + sh - i);
      sh++;
    }
    printf("Minimum exchange operations : %d\n", count);
  }*/
}
