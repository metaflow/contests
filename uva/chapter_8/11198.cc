#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

bitset<20> primes;

struct State;

struct State {
  int digits[8];
  int distance;
  friend ostream& operator << (ostream& stream, const State& s);
};

const uint encode(const State s) {
  uint c = 0;
  for (int i = 0; i < 8; i++) {
    if (s.digits[i] < 0) c++;
    c <<= 1;
  }
  c <<= 2;
  for (int i = 0; i < 8; i++) {
    if (i) c <<= 3;
    c += abs(s.digits[i]) & 7;
  }
  return c;
}

ostream& operator << (ostream& stream, const State& s) {
  for (int i = 0; i < 8; i++) stream << s.digits[i] << " ";
  stream << "= " << hex << encode(s) << dec;
  return stream;
}


bool fit(const int a, const int b) {
  return (a * b < 0) && primes[abs(a - b)];
}

void dance(State& n, State& s, int i, int j) {
  int a = 0;
  int b = 0;
  // move i-th digit before j-th
  int t = j;
  if (j > i) t--;
  while (b < 8) {
    if (a == i) { a++; continue; }
    if (b == t) { n.digits[b] = s.digits[i]; b++; continue; }
    n.digits[b] = s.digits[a];
    a++;
    b++;
  }
}

int main() {
  primes.set(3);
  primes.set(5);
  primes.set(7);
  primes.set(11);
  primes.set(13);

  State target;
  for (int i = 0; i < 8; i++) target.digits[i] = i + 1;
  uint key = encode(target);
/*
  State x = target;
  dance(x, target, 0, 1);
  cerr << x << endl;
  x = target;
  dance(x, target, 2, 1);
  cerr << x << endl;
  x = target;
  dance(x, target, 0, 7);
  cerr << x << endl;
  x = target;
  dance(x, target, 5, 3);
  cerr << x << endl;
  x = target;
  dance(x, target, 7, 0);
  cerr << x << endl;
  x = target;
  dance(x, target, 7, 2);
  cerr << x << endl;
  return 0;
*/
  // for (uint i = 0; i < (1u << 8); i++) {
  //   State s;
  //   for (int j = 0; j < 8; j++) {
  //     s.digits[j] = j + 1;
  //     if (i & (1u << j)) s.digits[j] = -s.digits[j];
  //   }
  //   // distance[encode(s)] = s.distance = 0;
  //   // q.emplace(s);
  //   cerr << s << endl;
  // }

  // return 0;

  for (int tc = 1;; tc++) {
    State s;
    int t;
    cin >> t;
    if (t == 0) break;
    s.digits[0] = t;
    for (int i = 1; i < 8; i++) {
      cin >> s.digits[i];
    }
    s.distance = 0;
    queue<State> q;
    q.emplace(s);
    set<uint> queued;
    queued.insert(encode(s));
    int ans = -1;
    while (!q.empty()) {
      State s = q.front(); q.pop();
      auto c = encode(s);
      if ((key & c) == key) {
         // cerr << s << endl;
         ans = s.distance;
         break;
      }
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if (!fit(s.digits[i], s.digits[j])) continue;
          State n = s;
          n.distance++;
          dance(n, s, i, j);
          c = encode(n);
          if (!queued.count(c)) {
            // cerr << "+ " << n << endl;
            queued.insert(c);
            q.emplace(n);
          }

          // swap this pair
          if (j > i) {
            swap(n.digits[j - 1], n.digits[j]);
          } else {
            swap(n.digits[j], n.digits[j + 1]);
          }

          c = encode(n);
          if (!queued.count(c)) {
            // cerr << "+ " << n << endl;
            queued.insert(c);
            q.emplace(n);
          }
        }
      }
    }
    printf("Case %d: %d\n", tc, ans);
  }
  return 0;
}

