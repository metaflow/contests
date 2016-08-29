#include <utility>
#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    bool first = true;
    while (cin >> n) {
        if (!first) cout << "\n";
        first = false;
        vector<string> names;
        string s;
        for (int i = 0; i < n; i++) {
            cin >> s;
            names.push_back(s);
        }
        map<string, pair<int, int> > balance;
        for (auto it = names.begin(); it != names.end(); it++) {
            balance[*it].first = 0;
            balance[*it].second = 0;
        }
        for (int i = 0; i < n; i++) {
            int v, k;
            cin >> s >> v >> k;
            if (k > 0) {
                int a = v / k;
                balance[s].first -= a * k;
                for (int j = 0; j < k; j++) {
                    string p;
                    cin >> p;
                    balance[p].second += a;
                }
            }
        }
        for (auto i = names.begin(); i != names.end(); i++) {
            cout << *i << " " << (balance[*i].first + balance[*i].second) << "\n";
        }
    }
    return 0;
}
