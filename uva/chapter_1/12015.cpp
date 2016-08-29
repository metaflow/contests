#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<string, int> site_rank;


int main() {
    int case_count;
    cin >> case_count;
    for (int case_number = 1; case_number <= case_count; case_number++) {
        vector<site_rank> sites;
        int m = -1;
        for (int i = 0; i < 10; i++) {
            site_rank r;
            cin >> r.first >> r.second;
            sites.push_back(r);
            m = max(m, r.second);
        }
        printf("Case #%d:\n", case_number);
        for (vector<site_rank>::iterator it = sites.begin();
            it != sites.end(); it++) {
            if (it->second != m) continue;
            printf("%s\n", it->first.c_str());
        }
    }
    return 0;
}
