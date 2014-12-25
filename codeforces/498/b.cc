#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 5005;
int n, T;

double memo[MAX][MAX];
int p[MAX], t[MAX];
double eps = 0.0001;

double f(int song, int left) {
  if (left == 0) return 0;
  if (song == n) return -1; // no chance
  double &r = memo[song][left];
  if (r + eps < -1) {
    r = 0;

    if (p[song] == 100) {
      r = f(song + 1, left - 1);
      if (r + eps < 0) return r;
      return r + 1;
    }

    if (p[song] == 0) {
      if (left < t[song]) return r = -1;
      r = f(song + 1, left - t[song]);
      if (r + eps < 0) return r;
      return r + 1;
    }

    //double v = 1; // unrecognized at the moment
    double e = p[song]; e /= 100;
    double u = 1 - e;
    for (int i = 1; i <= min(t[song] - 1, left); i++) {
      double g = f(song + 1, left - i);
      if (g + eps < 0) continue;
      r += pow(u, i - 1) * e * (1 + g);
      //v = pow(u, i);
    }
    if (t[song] <= left) {
      double g = f(song + 1, left - t[song]);
      if (!(g + eps < 0)) r += pow(u, t[song] - 1) * (1 + g);
    }
  }
  return r;
}

int main() {
  while (cin >> n >> T) {
    fill(&memo[0][0], &memo[MAX][0], -100);
    for (int i = 0; i < n; i++) cin >> p[i] >> t[i];
    double r = f(0, T);
    if (r < 0) r = 0;
    cout << r << endl;
  }
}
