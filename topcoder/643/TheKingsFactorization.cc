#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

class TheKingsFactorization {
    vector<ll> low_primes;

    void sieve() {
      bitset<50000> b;
      b.reset();
      low_primes.emplace_back(2);
      for (ll i = 3; i < b.size(); i+=2) {
        if (b[i]) continue;
        low_primes.emplace_back(i);
        for (ll j = i * i; j < b.size(); j+=i) b.set(j);
      }
    }

    bool is_prime(ll a) {
      auto p = low_primes.begin();
      while (p != low_primes.end() && (*p) * (*p) <= a) {
        if (a % *p == 0) return false;
        p++;
      }
      return true;
    }

    ll get_prime(ll a, ll b, ll n) {
      if (n % a == 0) return a;
      if (n % b == 0) return b;
      if (n >= a && n <= b && is_prime(n)) return n;
      for (ll i = a; i <= b; i++) {
        if (n % i != 0) continue;
        if (is_prime(i)) return i;
      }
      return n;
    }
    public:
    vector<long long> getVector(long long N, vector<long long> primes) {
      sieve();
      for (ll p : primes) N /= p;
      vector<ll> result;
      for (int i = 0; i < primes.size() * 2 - 1; i++) {
        if (i % 2 == 0) {
          result.emplace_back(primes[i / 2]);
          continue;
        }
        ll a = primes[i / 2];
        ll b = primes[i / 2 + 1];
        ll c = get_prime(a, b, N);
        N /= c;
        result.emplace_back(c);
      }
      if (N != 1) result.emplace_back(N);
      return result;
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector<long long> &Expected, const vector<long long> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { long long Arg0 = 12LL; long Arr1[] = {2, 3}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long Arr2[] = {2, 2, 3 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, getVector(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 7LL; long Arr1[] = {7}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long Arr2[] = {7 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, getVector(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 1764LL; long Arr1[] = {2, 3, 7}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long Arr2[] = {2, 2, 3, 3, 7, 7 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, getVector(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 49LL; long Arr1[] = {7}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long Arr2[] = {7, 7 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, getVector(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 210LL; long Arr1[] = {2, 5}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long Arr2[] = {2, 3, 5, 7 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, getVector(Arg0, Arg1)); }
	void test_case_5() { long long Arg0 = 100000LL; long Arr1[] = {2, 2, 2, 5, 5}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long Arr2[] = {2, 2, 2, 2, 2, 5, 5, 5, 5, 5 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(5, Arg2, getVector(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    TheKingsFactorization ___test;
    ___test.run_test(-1);
}
// END CUT HERE
