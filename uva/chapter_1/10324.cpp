#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    string s;
    int case_n = 0;
    while (cin >> s) {
        case_n++;
        vector<int> o;
        char p = '0';
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '0') {
                p = '0';
                continue;
            }
            if (p == '1') continue;
            p = '1';
            o.push_back(i);
        }
        int n, a, b;
        cin >> n;
        cout << "Case " << case_n << ":" << endl;
        while (n--) {
            cin >> a >> b;
            if (s[a] == s[b]) {
                auto ia = upper_bound(o.begin(), o.end(), a);
                auto ib = upper_bound(o.begin(), o.end(), b);
                if (ia == ib) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
            } else {
                cout << "No" << endl;
            }
        }
    }
}
