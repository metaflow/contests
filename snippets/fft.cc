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

typedef complex<double> base;
typedef complex<double> cd;
typedef vector<cd> vcd;

vcd fft(const vcd &as) {
  int n = as.size();
  int k = 0; // Длина n в битах
  while ((1 << k) < n) k++;
  vector<int> rev(n);
  rev[0] = 0;
  int high1 = -1;
  for (int i = 1; i < n; i++) {
    if ((i & (i - 1)) == 0) // Проверка на степень двойки. Если i ей является, то i-1 будет состоять из кучи единиц.
      high1++;
    rev[i] = rev[i ^ (1 << high1)]; // Переворачиваем остаток
    rev[i] |= (1 << (k - high1 - 1)); // Добавляем старший бит
  }

  vcd roots(n);
  for (int i = 0; i < n; i++) {
    double alpha = 2 * M_PI * i / n;
    roots[i] = cd(cos(alpha), sin(alpha));
  }

  vcd cur(n);
  for (int i = 0; i < n; i++)
    cur[i] = as[rev[i]];

  for (int len = 1; len < n; len <<= 1) {
    vcd ncur(n);
    int rstep = roots.size() / (len * 2);
    for (int pdest = 0; pdest < n;) {
      int p1 = pdest;
      for (int i = 0; i < len; i++) {
        cd val = roots[i * rstep] * cur[p1 + len];
        ncur[pdest] = cur[p1] + val;
        ncur[pdest + len] = cur[p1] - val;
        pdest++, p1++;
      }
      pdest += len;
    }
    cur.swap(ncur);
  }
  return cur;
}

vcd fft_rev(const vcd &as) {
  vcd res = fft(as);
  for (int i = 0; i < (int)res.size(); i++) res[i] /= as.size();
  reverse(res.begin() + 1, res.end());
  return res;
}
/*
vector<double> multiply (const vector<double> & a, const vector<double> & b) {
  vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
  size_t n = 1;
  while (n < max (a.size(), b.size()))  n <<= 1;
  n <<= 1;
  fa.resize (n),  fb.resize (n);

  fft (fa, false),  fft (fb, false);
  for (size_t i=0; i<n; ++i)
    fa[i] *= fb[i];
  fft (fa, true);

  vd res(n);
  for (size_t i=0; i<n; ++i)
    res[i] = fa[i].real();
  return res;
}
*/
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

const int mod = 7340033;
const int root = 5;
const int root_1 = 4404020;
const int root_pw = 1<<20;

vi dfft(vector<int> a, bool invert) {
  int n = (int) a.size();

  for (int i=1, j=0; i<n; ++i) {
    int bit = n >> 1;
    for (; j>=bit; bit>>=1)
      j -= bit;
    j += bit;
    if (i < j)
      swap (a[i], a[j]);
  }

  for (int len=2; len<=n; len<<=1) {
    int wlen = invert ? root_1 : root;
    for (int i=len; i<root_pw; i<<=1)
      wlen = int (wlen * 1ll * wlen % mod);
    for (int i=0; i<n; i+=len) {
      int w = 1;
      for (int j=0; j<len/2; ++j) {
        int u = a[i+j],  v = int (a[i+j+len/2] * 1ll * w % mod);
        a[i+j] = u+v < mod ? u+v : u+v-mod;
        a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
        w = int (w * 1ll * wlen % mod);
      }
    }
  }
  vi r(mod);
  r[1] = 1;
  for (int i=2; i<mod; ++i)
    r[i] = (mod - (mod/i) * r[mod%i] % mod) % mod;

  if (invert) {
    int nrev = r[n];
    for (int i=0; i<n; ++i)
      a[i] = int (a[i] * 1ll * nrev % mod);
  }
  return a;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vcd v = {2, 1, 1, 0, 0, 1, 1, 2};
  // vcd v = {0, 1, 1, 3, 1, 2, 2, 2};
  auto t = fft(v);
  // auto t = dfft(v, false);
  // vd a = {0, 0, 1, 1};
  // vd b = {1, 1, 1, 1};
  // vd c = multiply(a, b);
  for (auto i : t) {
    cout << abs(i) << endl;
    // cout << i << endl;
  }
  // print_range(cout, c.begin(), c.end()) << endl;
}
