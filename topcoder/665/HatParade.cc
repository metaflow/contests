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
const ll MOD = 1000000007;

class HatParade {
    public:

    void rm(ll i, ll j, vi& a, vi& b, vi& nb, ll n) {
      if (i > j) {
        rm(j, i, a, b, nb, n);
        return;
      }
      if (j != n - 1) {
        swap(a[j], a[n - 1]);
        swap(b[j], b[n - 1]);
        swap(nb[j], nb[n - 1]);
      }
      n--;
      swap(a[i], a[n - 1]);
      swap(b[i], b[n - 1]);
      swap(nb[i], nb[n - 1]);
    }

    ll f(ll P, ll S, ll T, vi& a, vi& b, vi& nb, ll n) {
      // cerr << "P " << P << " S " << S << " T " << T << " n " << n << endl;
      if (n == 0) return 1;
      set<int> L, R;
      for (ll i = 0; i < n; i++) {
        // cerr << "? " << a[i] << " " << b[i] << endl;
        if (b[i] < min(P, S) || nb[i] < min(P, S)) {
          cerr << "bad" << endl;
          return 0;
        }
        if ((b[i] == P + T && nb[i] == S + a[i]) ||
            (nb[i] == P + T && b[i] == S + a[i])) {
          // cerr << "R " << a[i] << " " << b[i] << endl;
          R.emplace(i);
        }
        if ((b[i] == S + T && nb[i] == P + a[i]) ||
            (nb[i] == S + T && b[i] == P + a[i])) {
          // cerr << "L " << a[i] << " " << b[i] << endl;
          L.emplace(i);
        }
      }
      // cerr << " " << R.size() << " & " << L.size() << endl;
      if (L.empty() || R.empty()) return 0;
      if (n == 1) return 1;
      set<int> Ronly, Lonly;
      vi both;
      for (auto i : R) {
        if (L.count(i)) {
          both.emplace_back(i);
        } else {
          Ronly.emplace(i);
        }
      }
      for (auto i : L) {
        if (R.count(i)) {
        } else {
          Lonly.emplace(i);
        }
      }
      ll result = 0;
      cerr << Lonly.size() << " x " << Ronly.size() << " x " << both.size() << endl;
      for (auto i : Lonly) {
        for (auto j : Ronly) {
          auto ca = a;
          auto cb = b;
          auto cnb = nb;
          rm(i, j, ca, cb, cnb, n);
          result = (result + f(P + a[i], S + a[j], T - a[i] - a[j], ca, cb, cnb, n - 2)) % MOD;
        }
      }
      for (auto i : Lonly) {
        for (auto j : both) {
          auto ca = a;
          auto cb = b;
          auto cnb = nb;
          rm(i, j, ca, cb, cnb, n);
          result = (result + f(P + a[i], S + a[j], T - a[i] - a[j], ca, cb, cnb, n - 2)) % MOD;
        }
      }
      for (auto i : both) {
        for (auto j : Ronly) {
          auto ca = a;
          auto cb = b;
          auto cnb = nb;
          rm(i, j, ca, cb, cnb, n);
          result = (result + f(P + a[i], S + a[j], T - a[i] - a[j], ca, cb, cnb, n - 2)) % MOD;
        }
      }
      for (ll i = 0; i < both.size(); i++) {
        for (ll j = i + 1; j < both.size(); j++) {
          auto ca = a;
          auto cb = b;
          auto cnb = nb;
          rm(both[i], both[j], ca, cb, cnb, n);
          result = (result + 2 * f(P + a[both[i]], S + a[both[j]], T - a[both[i]] - a[both[j]], ca, cb, cnb, n - 2)) % MOD;
        }
      }
      return result;
    }

    int getPermutation(vector <int> value, vector <int> sum) {
      ll n = value.size();
      ll T = accumulate(value.begin(), value.end(), 0);
      vi nb(n);
      for (ll i = 0; i < n; i++) nb[i] = T - sum[i] + value[i];
      return f(0, 0, T, value, sum, nb, n);
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 1, 1, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 2, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 1, 2, 1, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 2, 2, 1, 2, 1, 1, 2, 2, 2, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 1, 2, 1, 1, 2, 1, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 2, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 1, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 2, 1, 1, 2, 2, 2, 2, 2, 1, 2, 2, 1, 1, 1, 2, 2, 2, 1, 2, 2, 1, 1, 2, 1, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2, 1, 2, 2, 2, 2, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 1, 2, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {508, 583, 492, 431, 152, 481, 702, 69, 78, 333, 430, 359, 109, 4, 718, 550, 456, 465, 98, 285, 453, 440, 507, 613, 367, 593, 342, 55, 338, 691, 8, 382, 420, 579, 558, 252, 194, 561, 667, 441, 257, 573, 477, 47, 383, 309, 617, 231, 487, 89, 91, 191, 360, 111, 585, 347, 654, 728, 578, 377, 543, 201, 58, 591, 390, 384, 223, 703, 519, 416, 716, 681, 13, 722, 437, 606, 414, 62, 518, 588, 303, 254, 178, 650, 474, 609, 730, 525, 29, 86, 64, 554, 208, 120, 139, 643, 386, 110, 515, 325, 293, 148, 689, 735, 534, 28, 51, 335, 341, 199, 379, 391, 182, 309, 673, 156, 604, 129, 437, 611, 354, 324, 602, 691, 134, 167, 739, 282, 33, 554, 670, 736, 446, 479, 113, 65, 47, 421, 675, 73, 480, 441, 191, 516, 523, 400, 637, 400, 405, 174, 502, 350, 453, 32, 609, 220, 14, 458, 30, 641, 327, 27, 23, 124, 116, 517, 58, 254, 607, 212, 281, 221, 685, 282, 146, 286, 647, 187, 712, 20, 283, 575, 290, 35, 180, 86, 237, 183, 593, 736, 583, 653, 285, 703, 230, 563, 692, 100, 447, 131, 39, 488, 204, 375, 420, 644, 302, 300, 390, 567, 185, 106, 655, 705, 633, 640, 432, 514, 54, 375, 113, 189, 95, 676, 276, 395, 72, 26, 296, 699, 151, 408, 676, 628, 37, 485, 720, 93, 528, 130, 577, 291, 662, 596, 212, 495, 457, 585, 443, 362, 410, 626, 538, 633, 193, 582, 516, 250, 421, 251, 263, 746, 406, 481, 245, 650, 720, 492, 510, 302, 695, 103, 181, 707, 556, 518, 11, 701, 742, 317, 429, 659, 564, 234, 683, 190, 490, 25, 211, 316, 684, 445, 733, 358, 467, 438, 434, 165, 366, 304, 748, 611, 77, 589, 671, 244, 669, 371, 504, 345, 231, 53, 541, 363, 363, 682, 618, 661, 320, 556, 511, 103, 435, 248, 128, 115, 213, 534, 132, 43, 614, 587, 542, 378, 258, 746, 464, 123, 571, 329, 146, 28, 348, 473, 631, 59, 203, 635, 329, 681, 491, 246, 734, 473, 715, 107, 403, 401, 2, 2, 510, 580, 105, 340, 216, 417, 265, 200, 80, 106, 634, 204, 256, 126, 258, 20, 269, 389, 576, 216, 744, 439, 46, 227, 202, 90, 602, 100, 468, 22, 334, 387, 154, 206, 272, 575, 157, 485, 483, 41, 246, 670, 459, 527, 429, 162, 415, 512, 318, 229, 99, 598, 616, 227, 519, 172, 144, 14, 268, 471, 595, 306, 630, 379, 364, 297, 230, 225, 88, 696, 396, 356, 677, 464, 463, 454, 529, 545, 349, 275, 186, 748, 34, 425, 398, 152, 530, 12, 502, 349, 199, 455, 615, 708, 745, 444, 591, 343, 192, 179, 460, 83, 394, 325, 277, 619, 255, 414, 513, 475, 396, 537, 94, 57, 503, 253, 42, 667, 127, 184, 742, 413, 66, 695, 380, 131, 219, 734, 581, 456, 274, 205, 96, 300, 79, 88, 87, 207, 678, 38}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 845845078; verify_case(0, Arg2, getPermutation(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {9, 1, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, getPermutation(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {4, 4, 4, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {16, 16, 8, 8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(2, Arg2, getPermutation(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1, 2, 3, 4, 5, 6, 7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 27, 6, 22, 18, 21, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(3, Arg2, getPermutation(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
    HatParade ___test;
    ___test.run_test(0);
}
// END CUT HERE
