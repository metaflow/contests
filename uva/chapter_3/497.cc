#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int tcc;
    cin >> tcc;
    string s;
    getline(cin, s);
    getline(cin, s);
    for (int tc = 1; tc <= tcc; tc++) {
        if (tc != 1) cout << endl;
        vector<int> values;
        vector<int> refs;
        vector<int> lis;
        vector<int> lisref;
        while (getline(cin, s) && s.size() > 0) {
            int i = atoi(s.c_str());
            values.push_back(i);
            refs.push_back(-1);
            int idx = values.size() - 1;
            auto it = lower_bound(lis.begin(), lis.end(), i);
            int lis_idx;
            if (it == lis.end()) {
                lis.push_back(i);
                lisref.push_back(idx);
                it = lis.end() - 1;
                lis_idx = lis.size() - 1;
            } else {
                *it = i;
                lis_idx = it - lis.begin();
                lisref[lis_idx] = idx;
            }
            if (lis_idx) refs[idx] = lisref[lis_idx - 1];
        }
        cout << "Max hits: " << lis.size() << endl;
        vector<int> answer;
        int i = lisref.back();
        while (i != -1) {
            answer.push_back(values[i]);
            i = refs[i];
        }
        reverse(answer.begin(), answer.end());
        for (auto k : answer) cout << k << endl;
    }
}
