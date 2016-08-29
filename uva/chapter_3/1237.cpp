#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct maker {
    string name;
    int low, high;
};

int main() {
    int tcc;
    cin >> tcc;
    for (int tc = 1; tc <= tcc; tc++) {
        if (tc > 1) cout << endl;
        int d;
        cin >> d;
        vector<maker> mm;
        mm.reserve(d);
        for (int i = 0; i < d; ++i) {
            maker m;
            cin >> m.name >> m.low >> m.high;
            mm.push_back(m);
        }
        int q;
        cin >> q;
        while (q--) {
            int p;
            cin >> p;
            string name = "";
            for (auto m : mm) {
                if (m.low > p || m.high < p) continue;
                if (name == "") {
                    name = m.name;
                } else {
                    name = "UNDETERMINED";
                    break;
                }
            }
            if (name == "") name = "UNDETERMINED";
            cout << name << endl;
        }
    }
}
