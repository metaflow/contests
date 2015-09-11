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

struct trie;
using ptrie = shared_ptr<trie>;
struct trie {
  ptrie next[26];
};

ll insert(ptrie t, string& s, ll pos) {
  if (pos == s.size()) return pos;
  ll result = pos;
  int i = s[pos] - 'a';
  if (t->next[i]) {
    return insert(t->next[i], s, pos + 1);
  }
  t->next[i] = make_shared<trie>();
  insert(t->next[i], s, pos + 1);
  return pos + 1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ptrie root = make_shared<trie>();
    ll n; cin >> n;
    ll answer = 0;
    while (n--) {
      string s;
      cin >> s;
      answer += insert(root, s, 0);
    }
    cout << "Case #" << tc << ": " << answer << endl;
  }
}
