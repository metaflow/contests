#include <map>
#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
    int cases_count;
    cin >> cases_count;
    string s;
    getline(cin, s);
    getline(cin, s);
    while (cases_count--) {
        map<string, int> m;
        int total = 0;
        while (true) {
            getline(cin, s);
            if (s.empty()) break;
            if (s[s.length() - 1] == 13) s.resize(s.length() - 1);
            if (s.empty()) break;
            if (m.count(s) == 0) m[s] = 0;
            m[s]++;
            total++;
        }
        for (map<string,int>::iterator it = m.begin(); it != m.end(); it++) {
            double d = it->second * 100;
            d /= total;
            printf("%s %.4f\n", it->first.c_str(), d);
        }
        if (cases_count != 0) printf("\n");
    }
    return 0;
}
