#include <string>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;
    map<char, vector<int> > m;
    for (int i = 0; i < s.size(); i++) {
        m[s[i]].push_back(i);
    }
    int n;
    cin >> n;
    while (n--) {
        string q;
        cin >> q;
        int p = -1;
        bool found = true;
        int first = -1, last = -1;
        for (int i = 0; i < q.size(); i++) {
            char c = q[i];
            auto it = lower_bound(m[c].begin(), m[c].end(), p + 1);
            if (it == m[c].end()) {
                found = false;
                break;
            }
            p = *it;
            if (first == -1) first = p;
            last = p;
        }
        if (found) {
            printf("Matched %d %d\n", first, last);
        } else {
            printf("Not matched\n");
        }
    }
    return 0;
}
