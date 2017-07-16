#if defined(LOCAL)
#define PROBLEM_NAME "c"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#include <bits/stdc++.h>
#endif

using namespace std;
using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)

// finds lowest x: f(x) = true, x within [a, b), b if f(b - 1) = false
l binary_search_lower(l a, l b, function<bool(l)> f) {
  l count = b - a;
  while (count > 0) {
    l step = count / 2;
    l m = a + step;
    if (f(m)) {
      count = step;
    } else {
      a = m + 1;
      count -= step + 1;
    }
  }
  return a;
}

bool ask(l s, istream& cin, ostream& cout) {
  cout << "? " << s << endl;
  char c; cin >> c;
  return c == 'Y';
}

void solve(istream& cin, ostream& cout) {
  l answer = 0;
  while (1) {
    answer *= 10;
    answer += binary_search_lower(0, 9, [&](l x) {
        l t = answer + x;
        while (t < e9) t = t * 10 + 9;
        return ask(t, cin, cout);
      });
    if (answer == 0) answer = 1;
    if (answer % 10 == 9) {
      if (not ask((answer - 1) * 10, cin, cout)) break;
    } else {
      if (ask(answer + 1, cin, cout)) break;
    }
  }
  cout << "! " << answer << endl;
}

default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

double random_double() {
  return uniform_real_distribution<double>(0, 1)(source);
}

bool random_bool() {
  return random_in_range(0, 2) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size())];
  }
  return s;
}

int _random_test_size_from = 0;
int _random_test_size_to = 100;
int _random_test_count = 10;

void generate_random(l size, ostream& cout) {
  cout << random_in_range(1, e9 + 1) << lf;
}

void player_b(istream& hidden_state, ostream& log,
              istream& cin, ostream& cout) {
  l answer; hidden_state >> answer;
  l count = 64;
  while (count > 0) {
    count--;
    string s;
    cin >> s;
    if (s == "?") {
      l n;
      cin >> n;
      if (n < 1 or n > e9 * e9) {
        log << n << " out of range" << lf;
        return;
      }
      if ((n <= answer and to_string(n) <= to_string(answer)) or
          (n > answer and to_string(n) > to_string(answer))) {
        cout << "Y" << endl;
      } else {
        cout << "N" << endl;
      }
    } else {
      cin >> s;
      return;
    }
  }
  log << "> 64 tries" << lf;
}

bool solution_checker(istream& input, istream& /* expected */,
                      istream& actual, ostream& out) {
  string answer; input >> answer;
  answer = "! " + answer;
  string a, s;
  while (getline(actual, s)) {
    if (not s.empty()) a = s;
    out << s << lf;
  }
  out << "'" <<  answer << "' <> '" << a << "'" << endl;
  return answer == a;
};


int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  _custom_solution_checker = solution_checker;
  _generate_random_test = generate_random;
  _player_b = player_b;
  // _solve_brute = solve_brute;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
